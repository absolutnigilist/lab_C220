#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

template<typename T>
class MyClass {
	std::vector<T> data;																	//вектор для хранения хначений
	T lower_bound, upper_bound;																//границы вводимых значений

	bool isValid(const T& value) {															//функция для проверки валидности вводимых значений
		return(value >= this->lower_bound && value <= this->upper_bound);
	}
public:
	MyClass(T lower, T upper) :lower_bound(lower), upper_bound(upper) {}					//конструктор класса

	MyClass() = default;																	//конструктор по умолчанию сгенерирует компилятор																		
	~MyClass() = default;																	//дестуктор сгенерирует компилятор
	MyClass(const MyClass& other) = default;												//конструктор копирования сгенерирует компилятор
	MyClass(MyClass&& oter) = default;														//перемещающий конструктор копирования сгенерирует компилятор
	MyClass& operator=(const MyClass& other) = default;										//оператор присванивания сгенерирует компилятор
	MyClass& operator=(MyClass&& other) = default;											//перемещающий оператор присванивания сгенерирует компилятор

	void add(const std::initializer_list<T>& list) {										//метод для добавления значений				
		for (const auto& val : list) {														//пробегаем по вектору
			if (isValid(val) && std::find(data.begin(), data.end(), val) == data.end()) {	//если совпадений не найдено и значение валидно
				data.push_back(val);														//добавляем в вектор
			}
		}
	}
	void del(const std::initializer_list<T>& list) {										//метод для удаления значений
		for (const auto& val : list) {														//пробегаем по ветору
			auto it = std::find(data.begin(), data.end(), val);								//если совпдание найдено, find вернет итератор
			if (it != data.end()) {
				data.erase(it);																//erase удаляет элемент
			}
		}
	}
	void setLowerBound(const T& val){														//set для нижней границы
		this->lower_bound=val;
	}
	void setUpperBound(const T& val) {														//set для верхней границы
		this->upper_bound = val;
	}
	template<typename Compare>																//шаблон метода класса для сортировки элементов вектора
	void sort(Compare comparator) {
		std::sort(data.begin(), data.end(), comparator);
	}
	size_t size() const{																			//метод для определения размера вектора
		return data.size();
	}
	bool contains(const T& value) {															//метод для поиска значений в векторе
		return std::find(data.begin(), data.end(), value) != data.end();
	}
	void clear() {
		data.clear();
	}
	T& operator[](size_t index) {
		return data[index];
	}
	typename std::vector<T>::iterator begin() {
		return data.begin();
	}
	typename std::vector<T>::iterator end() {
		return data.end();
	}
	typename std::vector<T>::const_iterator begin() const {
		return data.begin();
	}
	typename std::vector<T>::const_iterator end() const{
		return data.end();
	}
};