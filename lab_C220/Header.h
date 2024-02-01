#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <map>

template<typename T>
void PrintAnyCont(T& t) {					//������ ������� ��� ������ ����������
	for (const auto& cont : t) {			//� ������� range-based for ��������� �� ����������
		std::cout << cont << ", ";			//������� �������� �� ������
	}
	std::cout << std::endl;
}

template<typename T>						//������������� ������� ��� �������� ��������������� ����
void isType(T& t,std::true_type) {			//������ ������� ��� �������� ��������
	for (auto& val : t) {					//� ������� range-based for ��������� �� ����������
		val = -val;							//�������� �������� 
	}
}
template<typename T>						//������������� ������� ��� �������� �����������
void isType(T& t,std::false_type) {
	for (auto& val:t) {
		for (auto& str : val) {
			if (std::isalpha(str))			//���� ������ �����
			{
				str = std::isupper(str) ? std::tolower(str) : std::toupper(str);//������ �������
			}
		}
	}
}
template<typename T>
void NegateAll(T& t) {
	using Valuetype = typename std::remove_reference<decltype(*std::begin(t))>::type;//���������� ��� ���������
	isType(t, std::is_arithmetic<Valuetype>());										//�������� ������������� �����
}


template<typename T>						//������ ������� ��� ���������� �� ������
void absSort(T& t) {
	std::sort(std::begin(t), std::end(t),	//���������� ����������� ������� sort()� ������ ������� ������� ��������� �� ������ � �����
		[](const auto& a, const auto& b) {	//� ������� ������-������� ��������� ���������
			return std::abs(a) < std::abs(b); 
		}
	);
}

template<typename T, typename U>																		//������ ������� ��� ������������ �������� ����������� 
auto SumCont(const T& t, const U& u) {
	using SumType = decltype(*std::begin(t) + *std::begin(u));											//����� ������� ���������� c ������� decltype ���������� ��� ���������� 

	std::vector<SumType> result(std::max(std::size(t), std::size(u)), SumType());						//������� ������ ������ ���� <SumType> �������� �������� ����������
	auto minSize = std::min(std::size(t), std::size(u));												//������� ����������� ������ �� ���� �������� ����������
	std::transform(std::begin(t), std::next(std::begin(t), minSize), std::begin(u), std::begin(result),	//� ������� transform � ��������� ��������� ������ ����������� ����������� ��������
		[](const auto& a, const auto& b) {
			return a + b;
		}
	);
	if (std::size(t) > std::size(u))																	//�������� ���������� �������� ��������� �������� ���������� � �������� ������
	{
		std::copy(std::next(std::begin(t), minSize), std::end(t), std::next(std::begin(result), minSize));
	}
	else
	{
		std::copy(std::next(std::begin(u), minSize), std::end(u), std::next(std::begin(result), minSize));
	}
	return result;																						
}

//template<typename T, typename ContainerOne, typename ContainerTwo,typename Predicate>
//void Separate(const T& t, ContainerOne & one, ContainerTwo& two,Predicate predicate) {
//	std::copy_if(std::begin(t), std::next(std::begin(t),std::size(t)), std::inserter(one, one.end()), predicate);
//	std::copy_if(std::begin(t), std::next(std::begin(t),std::size(t)), std::inserter(two, two.end()),
//		[&](const auto& elem) {
//			return !predicate(elem);
//		}
//	);
//}

template<typename T, typename ContainerOne, typename ContainerTwo, typename Predicate>					//������ ������� ��� ���������� �������� ������ �� �������� �� �����������		
void Separate(const T& t, ContainerOne& one, ContainerTwo& two, Predicate predicate) {					//������� ��������� �� ������ �������� ���������, ��� �������� ���������� � ��������
	std::copy_if(std::begin(t), std::end(t), std::inserter(one, one.end()), predicate);					//�� ������ ��������� ��������� ������ ��������� ��������� ����������
	std::copy_if(std::begin(t), std::end(t),std::inserter(two, two.end()),								//�� ������ ��������� ������-������� ��������� ������ ��������� ������� ����������
		[&](const auto& elem) {
			return !predicate(elem);
		}
	);
}

enum class COLORS:unsigned char {BLUE,GREEN,RED};														

template<typename T>
std::map<std::string, T> stringEnumMap;

template<>
std::map<std::string, COLORS>stringEnumMap<COLORS> {
	{"blue",COLORS::BLUE},
	{"green",COLORS::GREEN},
	{"red",COLORS::RED}
};

template<typename T>
std::string enumToString(const T& t) {
	for (const auto& pair: stringEnumMap<T>)
	{
		if (pair.second==t)
		{
			return pair.first;
		}
	}throw std::runtime_error("Enum value not foud");
}

template<typename T>
T stringToEnum(const std::string& str) {
	auto it = stringEnumMap<T>.find(str);
	if (it!= stringEnumMap<T>.end())
	{
		return it->second;
	}throw std::runtime_error("String value not found");
}