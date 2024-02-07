#pragma once
#include <initializer_list>
#include <stdexcept>
#include <iostream>

template<typename T>
void Print(const T& t) {
	for (const auto& el : t) {
		std::cout << el << ' ';
	}
	std::cout << std::endl;
}

template<typename T>
class MyQueue {
	
	
	size_t head;			//������ ������� �������� � �������
	size_t tail;			//������ ������� ����������
	size_t size;			//���������� ���������� ��������� � �������
	size_t capacity;		//�������
	T* data;				//��������� �� ������ ������������� �������
	class iterator {		//���������� ����� ��������

		const MyQueue* m_pQ;
		int m_i;
	public:
		iterator() :m_pQ(nullptr), m_i(0) {}						//��������� ����������� ���������
		iterator(const MyQueue* pQ, int i) :m_pQ(pQ), m_i(i) {}		//����������� � �����������
		iterator& operator++() {									//�������� ++
			if (m_pQ != nullptr)
			{
				m_i = (m_i + 1) % m_pQ->capacity;
			}
			return *this;
		}
		T operator*() {												//�������� �������������
			if (m_pQ != nullptr)
			{
				return m_pQ->data[m_i % m_pQ->capacity];
			}
			throw std::out_of_range("Iterator out of range");
		}
		bool operator!=(const iterator& other)const {				//�������� ��������� �� ���������
			return m_i != other.m_i;
		}
	};
	
public:

	MyQueue():capacity(2), size(0), head(0),tail(0), data(new T[capacity]) {};																	//����������� �� ���������
	MyQueue(std::initializer_list<T> list):MyQueue() {																							//����������� � �����������																						
		for (const auto& val : list) {
			push(val);
		} 
	}																																																																																			
	MyQueue(const MyQueue& other) :size(other.size), capacity(other.size+1), head(0), tail(other.size), data(new T[capacity]) {//����������� �����������
		for (size_t i = 0; i < other.size; ++i)
		{
			data[i] = other.data[(other.head+i)%other.capacity];
		}
	}
	MyQueue(MyQueue&& other)noexcept :head(other.head), tail(other.tail), size(other.size), capacity(other.capacity),data(other.data) {			//move ����������� �����������
		other.data = nullptr;
		other.size = 0;
		other.capacity = 1;
	}
	MyQueue(size_t n, const T& val) : capacity(n+1), size(n), head(0), tail(0), data(new T[capacity]) {											//������������� ����������� � �����������
		for (size_t i = 0; i < n; ++i) {
			data[i] = val;
		}
		tail = n % capacity;
	}
	MyQueue& operator=(const MyQueue& other) {
		if (this != &other) { // �������� �� ����������������
			if (other.size >= capacity) {
				// ��������� ����������������� ������
				T* new_data = new T[other.size + 1];
				for (size_t i = 0; i < other.size; ++i) {
					new_data[i] = other.data[(other.head + i) % other.capacity];
				}
				delete[] data;
				data = new_data;
				capacity = other.size+1;
			}
			else 
			{
				// ����������������� �� ���������, ������ �������� ��������
				for (size_t i = 0; i < other.size; ++i) {
					data[i] = other.data[(other.head + i) % other.capacity];
				}
				// ��� ���������, ������� ����� ���������� � ������ ������ � �� ���������������� ������, ������� �� ���������
			}
			size = other.size;
			head = 0;
			tail = size % capacity; // ��������� tail �������� ������ �������
		}
		return *this;
	}
	MyQueue& operator=(std::initializer_list<T> list) {																							//������������� �������� ������������
		
		delete[]data;
		capacity = list.size() + 1;
		size = 0;
		data = new T[capacity];
		head = 0;
		tail = 0;
		
		for (auto& val:list) {
			push(val);
		}
		return *this;
	}
	MyQueue& operator=(MyQueue&& other) noexcept {
		if (this != &other) { // �������� �� ����������������
			delete[] data; // ����������� ������������ �������

			// ��������� �������� ��������� �� other � *this
			data = other.data;
			size = other.size;
			capacity = other.capacity;
			head = other.head;
			tail = other.tail;

			// �������� ������� � other
			other.data = nullptr;
			other.size = 0;
			other.capacity = 0;
			other.head = 0;
			other.tail = 0;
		}
		return *this;
	}

	
	~MyQueue() {																																//����������
			delete[]data;
	}
	void push(T value) {																														//����� ��� ���������� ��������
		if (size==capacity-1)
		{
			resize(capacity + 1);
		}
		data[tail] = std::move(value);
		tail = (tail + 1) % capacity;
		size++;
	}
	T pop() {																																	//����� ��� �������� 1-�� ��������
		if (size==0)
		{
			throw std::out_of_range("Queue is empty");
		}
		T result=std::move(data[head]);
		head = (head + 1) % capacity;
		--size;
		return result;

	}
	
	void resize(size_t new_capacity) {																											//����� ��� ��������� ������� ����������
		if (new_capacity < size) {
			throw std::invalid_argument("New capacity must be greater than or equal to the current size.");
		}
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < size; ++i)
		{
			new_data[i] = std::move(data[(head + i) % capacity]);
		}
		delete[]data;
		data = new_data;
		head = 0;
		tail = size;
		capacity = new_capacity;
	}																 
	
	iterator begin() const{																						//��������� �� ������								
		return iterator(this, head);
	}
	iterator end() const {																						//�������� �� ����� ����������
		return iterator(this, tail);
	}

};