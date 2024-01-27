#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <map>

template<typename T>
void PrintAnyCont(T& t) {					//шаблон функции дл€ печати контейнера
	for (const auto& cont : t) {			//с помощью range-based for пробегаем по контейнеру
		std::cout << cont << ", ";			//выводим значени€ на печать
	}
	std::cout << std::endl;
}

template<typename T>						
void NegateAll(T& t) {						//шаблон функции дл€ инверсии значений
	for (auto& val : t) {					//с помощью range-based for пробегаем по контейнеру
		val = -val;							//инверси€ значений
	}
}

template<>									//специалищаци€ шаблонной функции
void NegateAll(std::list<std::string>& ls) {//дл€ контейнера типа list<string>
	for (auto& str : ls) {					//с помощью range-based for пробегаем по контейнеру
		for (auto& ch : str) {				//с помощью range-based for пробегаем по строкам
			if (std::isalpha(ch))			//если символ буква
			{
				ch = std::isupper(ch) ? std::tolower(ch) : std::toupper(ch);//мен€ем регистр
			}
		}
	}
}

template<typename T>						//шаблон функции дл€ сортировки по модулю
void absSort(T& t) {
	std::sort(std::begin(t), std::end(t),	//используем стандартную функцию sort()б внутри функции находим итераторы на начало и конец
		[](const auto& a, const auto& b) {	//с помощью л€мбда-функции сортируем контейнер
			return std::abs(a) < std::abs(b); 
		}
	);
}

template<typename T, typename U>																		//шаблон функции дл€ суммировани€ значений контейнеров 
auto SumCont(const T& t, const U& u) {
	using SumType = decltype(*std::begin(t) + *std::begin(u));											//после не€ного приведени€ c помощью decltype определ€ем тип контейнера 

	std::vector<SumType> result(std::max(std::size(t), std::size(u)), SumType());						//создаем пустой вектор типа <SumType> размером бќльшего контейнера
	auto minSize = std::min(std::size(t), std::size(u));												//находим минимальный размер из двух исходных контйенров
	std::transform(std::begin(t), std::next(std::begin(t), minSize), std::begin(u), std::begin(result),	//с помощью transform и предиката заполн€ем вектор минимальным количеством значений
		[](const auto& a, const auto& b) {
			return a + b;
		}
	);
	if (std::size(t) > std::size(u))																	//копируем оставшиес€ элементы исходного бќльшего контейнера в итоговый вектор
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

template<typename T, typename ContainerOne, typename ContainerTwo, typename Predicate>					//шаблон функции дл€ сортировки значений исход€ из четности по контейнерам		
void Separate(const T& t, ContainerOne& one, ContainerTwo& two, Predicate predicate) {					//функци€ принимает по ссылке исходный контейнер, два конечных контейнера и предикат
	std::copy_if(std::begin(t), std::end(t), std::inserter(one, one.end()), predicate);					//на основе предиката заполн€ем первый контейнер нечетными значени€ми
	std::copy_if(std::begin(t), std::end(t),std::inserter(two, two.end()),								//на основе предиката л€мбда-функции заполн€ем второй контейнер четными значени€ми
		[&](const auto& elem) {
			return !predicate(elem);
		}
	);
}

enum class COLORS:unsigned char {BLUE,GREEN,RED};														

template<typename T>																					
std::map<T,std::string> enumToStringMap;

template<typename T>
std::map<std::string, T> stringToEnumMap;

template<>
std::map<COLORS, std::string> enumToStringMap<COLORS> {
	{COLORS::BLUE,"blue"},
	{COLORS::GREEN,"green"},
	{COLORS::RED,"red"}

};
template<>
std::map<std::string, COLORS>stringToEnumMap<COLORS> {
	{"blue",COLORS::BLUE},
	{"green",COLORS::GREEN},
	{"red",COLORS::RED}
};

template<typename T>
std::string enumToString(const T& t) {
	auto it = enumToStringMap<T>.find(t);
	if (it!=enumToStringMap<T>.end())
	{
		return it->second;
	}
	throw std::runtime_error("Enum value not foud");
}

template<typename T>
T stringToEnum(const std::string& str) {
	auto it = stringToEnumMap<T>.find(str);
	if (it!=stringToEnumMap<T>.end())
	{
		return it->second;
	}throw std::runtime_error("String value not found");
}