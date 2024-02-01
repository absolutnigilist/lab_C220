#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

template<typename T>
class MyClass {
	std::vector<T> data;																	//������ ��� �������� ��������
	T lower_bound, upper_bound;																//������� �������� ��������

	bool isValid(const T& value) {															//������� ��� �������� ���������� �������� ��������
		return(value >= this->lower_bound && value <= this->upper_bound);
	}
public:
	MyClass(T lower, T upper) :lower_bound(lower), upper_bound(upper) {}					//����������� ������

	MyClass() = default;																	//����������� �� ��������� ����������� ����������																		
	~MyClass() = default;																	//��������� ����������� ����������
	MyClass(const MyClass& other) = default;												//����������� ����������� ����������� ����������
	MyClass(MyClass&& oter) = default;														//������������ ����������� ����������� ����������� ����������
	MyClass& operator=(const MyClass& other) = default;										//�������� ������������� ����������� ����������
	MyClass& operator=(MyClass&& other) = default;											//������������ �������� ������������� ����������� ����������

	void add(const std::initializer_list<T>& list) {										//����� ��� ���������� ��������				
		for (const auto& val : list) {														//��������� �� �������
			if (isValid(val) && std::find(data.begin(), data.end(), val) == data.end()) {	//���� ���������� �� ������� � �������� �������
				data.push_back(val);														//��������� � ������
			}
		}
	}
	void del(const std::initializer_list<T>& list) {										//����� ��� �������� ��������
		for (const auto& val : list) {														//��������� �� ������
			auto it = std::find(data.begin(), data.end(), val);								//���� ��������� �������, find ������ ��������
			if (it != data.end()) {
				data.erase(it);																//erase ������� �������
			}
		}
	}
	void setLowerBound(const T& val){														//set ��� ������ �������
		this->lower_bound=val;
	}
	void setUpperBound(const T& val) {														//set ��� ������� �������
		this->upper_bound = val;
	}
	template<typename Compare>																//������ ������ ������ ��� ���������� ��������� �������
	void sort(Compare comparator) {
		std::sort(data.begin(), data.end(), comparator);
	}
	size_t size() const{																			//����� ��� ����������� ������� �������
		return data.size();
	}
	bool contains(const T& value) {															//����� ��� ������ �������� � �������
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