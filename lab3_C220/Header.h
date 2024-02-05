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
	MyQueue(const MyQueue& other) :data(new T[other.capacity]), size(other.size), capacity(other.capacity), head(other.head), tail(other.tail) {//����������� �����������
		for (size_t i = 0; i < other.size; ++i)
		{
			data[(head + i) % capacity] = other.data[(other.head+i)%other.capacity];
		}
	}
	MyQueue(MyQueue&& other)noexcept :head(other.head), tail(other.tail), size(other.size), capacity(other.capacity),data(other.data) {			//move ����������� �����������
		other.data = nullptr;
		other.size = 0;
		other.capacity = 2;
	}
	MyQueue(size_t n, const T& val) : capacity(n+1), size(n), head(0), tail(0), data(new T[capacity]) {											//������������� ����������� � �����������
		for (size_t i = 0; i < n; ++i) {
			data[i] = val;
		}
		tail = n % capacity;
	}
	MyQueue& operator=(const MyQueue& other) {																									//�������� ������������
		if (this!=&other)
		{
			T* new_data = new T[other.capacity];
			for (size_t i = 0; i < other.size; ++i)
			{
				new_data[i] = other.data[(other.head + 1) % other.capacity];
			}
			delete[]data;
			data = new_data;
			size = other.size;
			capacity = other.capacity;
			head = 0;
			tail = other.size;
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
	//MyQueue& operator=(MyQueue other) {																										//�������� ������������
	//	swap(*this, other);
	//	return *this;
	//}
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
		
		if (new_capacity<size)
		{
			new_capacity = size;
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
	/*static void swap(MyQueue& first, MyQueue& second) {
		using std::swap;
		swap(first.head, second.head);
		swap(first.tail, second.tail);
		swap(first.size, second.size);
		swap(first.capacity, second.capacity);
		swap(first.data, second.data);
	}	*/																				 
	
	iterator begin() const{																						//��������� �� ������								
		return iterator(this, head);
	}
	iterator end() const {																						//�������� �� ����� ����������
		return iterator(this, tail);
	}

};