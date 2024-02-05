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
	
	
	size_t head;			//индекс первого элемента в очереди
	size_t tail;			//индекс первого свободного
	size_t size;			//актуальное количество элементов в очереди
	size_t capacity;		//емкость
	T* data;				//указатель на начало динамического массива
	class iterator {		//встроенный класс итератор

		const MyQueue* m_pQ;
		int m_i;
	public:
		iterator() :m_pQ(nullptr), m_i(0) {}						//дефолтный конструктор итератора
		iterator(const MyQueue* pQ, int i) :m_pQ(pQ), m_i(i) {}		//конструктор с параметрами
		iterator& operator++() {									//оператор ++
			if (m_pQ != nullptr)
			{
				m_i = (m_i + 1) % m_pQ->capacity;
			}
			return *this;
		}
		T operator*() {												//оператор разэменования
			if (m_pQ != nullptr)
			{
				return m_pQ->data[m_i % m_pQ->capacity];
			}
			throw std::out_of_range("Iterator out of range");
		}
		bool operator!=(const iterator& other)const {				//оператор сравнения на равенство
			return m_i != other.m_i;
		}
	};
	
public:

	MyQueue():capacity(2), size(0), head(0),tail(0), data(new T[capacity]) {};																	//конструктор по умолчанию
	MyQueue(std::initializer_list<T> list):MyQueue() {																							//конструктор с параметрами																						
		for (const auto& val : list) {
			push(val);
		} 
	}																																																																																			
	MyQueue(const MyQueue& other) :data(new T[other.capacity]), size(other.size), capacity(other.capacity), head(other.head), tail(other.tail) {//консутрктор копирования
		for (size_t i = 0; i < other.size; ++i)
		{
			data[(head + i) % capacity] = other.data[(other.head+i)%other.capacity];
		}
	}
	MyQueue(MyQueue&& other)noexcept :head(other.head), tail(other.tail), size(other.size), capacity(other.capacity),data(other.data) {			//move конструктор копирования
		other.data = nullptr;
		other.size = 0;
		other.capacity = 2;
	}
	MyQueue(size_t n, const T& val) : capacity(n+1), size(n), head(0), tail(0), data(new T[capacity]) {											//перегруженный конструктор с параметрами
		for (size_t i = 0; i < n; ++i) {
			data[i] = val;
		}
		tail = n % capacity;
	}
	MyQueue& operator=(const MyQueue& other) {																									//оператор присваивания
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
	MyQueue& operator=(std::initializer_list<T> list) {																							//перегруженный оператор присваивания
		
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
	//MyQueue& operator=(MyQueue other) {																										//оператор присваивания
	//	swap(*this, other);
	//	return *this;
	//}
	~MyQueue() {																																//деструктор
			delete[]data;
	}
	void push(T value) {																														//метод для добавления элемента
		if (size==capacity-1)
		{
			resize(capacity + 1);
		}
		data[tail] = std::move(value);
		tail = (tail + 1) % capacity;
		size++;
	}
	T pop() {																																	//метод для удаления 1-го элемента
		if (size==0)
		{
			throw std::out_of_range("Queue is empty");
		}
		T result=std::move(data[head]);
		head = (head + 1) % capacity;
		--size;
		return result;

	}
	void resize(size_t new_capacity) {																											//метод для изменения размера контейнера
		
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
	
	iterator begin() const{																						//итератора на начало								
		return iterator(this, head);
	}
	iterator end() const {																						//итератор на конец контейнера
		return iterator(this, tail);
	}

};