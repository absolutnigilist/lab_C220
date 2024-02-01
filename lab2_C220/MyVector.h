#pragma once
#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

template<typename T>
class MyVector: private std::vector<T> {
	T lower_bound, upper_bound;
	bool isValid(const T& value) {
		return (value >= this->lower_bound && value <= this->upper_bound);
	}
public:
	MyVector(const T& lower, const T& upper) :lower_bound(lower), upper_bound(upper) {}

	MyVector() = default;																	//конструктор по умолчанию сгенерирует компилятор																		
	~MyVector() = default;																	//дестуктор сгенерирует компилятор
	MyVector(const MyVector& other) = default;												//конструктор копирования сгенерирует компилятор
	MyVector(MyVector&& oter) = default;														//перемещающий конструктор копирования сгенерирует компилятор
	MyVector& operator=(const MyVector& other) = default;										//оператор присванивания сгенерирует компилятор
	MyVector& operator=(MyVector&& other) = default;											//перемещающий оператор присванивания сгенерирует компилятор
	
	void add(const std::initializer_list<T>& list) {
		for (const auto& val : list) {
			if (isValid(val)&&std::find(this->begin(),this->end(),val)==this->end())
			{
				this->push_back(val);
			}
		}
	}
	void setLowerBound(const T& val) {
		this->lower_bound = val;
	}
	void setUpperBound(const T& val) {
		this->upper_bound = val;
	}

	void del(const std::initializer_list<T>& list) {
		for (const auto& val : list) {
			auto it = std::find(this->begin(),this->end(),val);
			if (it != this->end()) {
				this->erase(it);
			}

		}
	}
	template<typename Compare>
	void sort(Compare comparator) {
		std::sort(this->begin(), this->end(), comparator);
	}
	size_t size() const {
		return std::vector<T>::size();
	}
	bool contains(const T& val) {
		return(std::find(this->begin(), this->end(), val) != this->end());
	}
	void clear() {
		std::vector<T>::clear();
	}
	T& operator[](size_t index) {
		return std::vector<T>::operator[](index);
	}
	typename std::vector<T>::iterator begin() {
		return std::vector<T>::begin();
	}
	typename std::vector<T>::iterator end() {
		return std::vector<T>::end();
	}
	typename std::vector<T>::const_iterator begin()const {
		return std::vector<T>::begin();
	}
	typename std::vector<T>::const_iterator end()const {
		return std::vector<T>::end();
	}
};
