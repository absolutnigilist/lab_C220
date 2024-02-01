#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <map>

template<typename T>
void PrintAnyCont(T& t) {					//шаблон функции для печати контейнера
	for (const auto& cont : t) {			//с помощью range-based for пробегаем по контейнеру
		std::cout << cont << ", ";			//выводим значения на печать
	}
	std::cout << std::endl;
}

template<typename T>						//перегруженная функция для инверсии арифметического типа
void isType(T& t,std::true_type) {			//шаблон функции для инверсии значений
	for (auto& val : t) {					//с помощью range-based for пробегаем по контейнеру
		val = -val;							//инверсия значений 
	}
}
template<typename T>						//перегруженная функция для инверсии контецнеров
void isType(T& t,std::false_type) {
	for (auto& val:t) {
		for (auto& str : val) {
			if (std::isalpha(str))			//если символ буква
			{
				str = std::isupper(str) ? std::tolower(str) : std::toupper(str);//меняем регистр
			}
		}
	}
}
template<typename T>
void NegateAll(T& t) {
	using Valuetype = typename std::remove_reference<decltype(*std::begin(t))>::type;//определяем тип параметра
	isType(t, std::is_arithmetic<Valuetype>());										//вызываем перегруженный метод
}


template<typename T>						//шаблон функции для сортировки по модулю
void absSort(T& t) {
	std::sort(std::begin(t), std::end(t),	//используем стандартную функцию sort()б внутри функции находим итераторы на начало и конец
		[](const auto& a, const auto& b) {	//с помощью лямбда-функции сортируем контейнер
			return std::abs(a) < std::abs(b); 
		}
	);
}

template<typename T, typename U>																		//шаблон функции для суммирования значений контейнеров 
auto SumCont(const T& t, const U& u) {
	using SumType = decltype(*std::begin(t) + *std::begin(u));											//после неяного приведения c помощью decltype определяем тип контейнера 

	std::vector<SumType> result(std::max(std::size(t), std::size(u)), SumType());						//создаем пустой вектор типа <SumType> размером бОльшего контейнера
	auto minSize = std::min(std::size(t), std::size(u));												//находим минимальный размер из двух исходных контйенров
	std::transform(std::begin(t), std::next(std::begin(t), minSize), std::begin(u), std::begin(result),	//с помощью transform и предиката заполняем вектор минимальным количеством значений
		[](const auto& a, const auto& b) {
			return a + b;
		}
	);
	if (std::size(t) > std::size(u))																	//копируем оставшиеся элементы исходного бОльшего контейнера в итоговый вектор
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

template<typename T, typename ContainerOne, typename ContainerTwo, typename Predicate>					//шаблон функции для сортировки значений исходя из четности по контейнерам		
void Separate(const T& t, ContainerOne& one, ContainerTwo& two, Predicate predicate) {					//функция принимает по ссылке исходный контейнер, два конечных контейнера и предикат
	std::copy_if(std::begin(t), std::end(t), std::inserter(one, one.end()), predicate);					//на основе предиката заполняем первый контейнер нечетными значениями
	std::copy_if(std::begin(t), std::end(t),std::inserter(two, two.end()),								//на основе предиката лямбда-функции заполняем второй контейнер четными значениями
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