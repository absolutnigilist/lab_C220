#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

template<typename T>
void PrintAnyCont(T& t) {					//шаблон функции для печати контейнера
	for (const auto& cont : t) {			//с помощью range-based for пробегаем по контейнеру
		std::cout << cont << ", ";			//выводим значения на печать
	}
	std::cout << std::endl;
}

template<typename T>						
void NegateAll(T& t) {						//шаблон функции для инверсии значений
	for (auto& val : t) {					//с помощью range-based for пробегаем по контейнеру
		val = -val;							//инверсия значений
	}
}

template<>									//специалищация шаблонной функции
void NegateAll(std::list<std::string>& ls) {//для контейнера типа list<string>
	for (auto& str : ls) {					//с помощью range-based for пробегаем по контейнеру
		for (auto& ch : str) {				//с помощью range-based for пробегаем по строкам
			if (std::isalpha(ch))			//если символ буква
			{
				ch = std::isupper(ch) ? std::tolower(ch) : std::toupper(ch);//меняем регистр
			}
		}
	}
}

template<typename T>						//шаблон функции для сортировки по модулю
void absSort(T& t) {
	std::sort(std::begin(t), std::end(t),	//используем стандартную функцию sort()б внутри функции находим итераторы на начало и конец
		[](const auto& a, const auto& b) {	//с помощью лямбда-функции сортируем контейнер
			return std::abs(a) < std::abs(b); 
		}
	);
}

template<typename T, typename U>
auto SumCont(const T& t, const U& u) {
	using SumType = decltype(*std::begin(t) + *std::begin(u));

	std::vector<SumType> result(std::max(std::size(t), std::size(u)), SumType());
	auto minSize = std::min(std::size(t), std::size(u));
	std::transform(std::begin(t), std::next(std::begin(t), minSize), std::begin(u), std::begin(result),
		[](const auto& a, const auto& b) {
			return a + b;
		}
	);
	if (std::size(t) > std::size(u))
	{
		std::copy(std::next(std::begin(t), minSize), std::end(t), std::next(std::begin(result), minSize));
	}
	else
	{
		std::copy(std::next(std::begin(u), minSize), std::end(u), std::next(std::begin(result), minSize));
	}
	return result;
}
