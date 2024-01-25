#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

template<typename T>
void PrintAnyCont(T& t) {					//������ ������� ��� ������ ����������
	for (const auto& cont : t) {			//� ������� range-based for ��������� �� ����������
		std::cout << cont << ", ";			//������� �������� �� ������
	}
	std::cout << std::endl;
}

template<typename T>						
void NegateAll(T& t) {						//������ ������� ��� �������� ��������
	for (auto& val : t) {					//� ������� range-based for ��������� �� ����������
		val = -val;							//�������� ��������
	}
}

template<>									//������������� ��������� �������
void NegateAll(std::list<std::string>& ls) {//��� ���������� ���� list<string>
	for (auto& str : ls) {					//� ������� range-based for ��������� �� ����������
		for (auto& ch : str) {				//� ������� range-based for ��������� �� �������
			if (std::isalpha(ch))			//���� ������ �����
			{
				ch = std::isupper(ch) ? std::tolower(ch) : std::toupper(ch);//������ �������
			}
		}
	}
}

template<typename T>						//������ ������� ��� ���������� �� ������
void absSort(T& t) {
	std::sort(std::begin(t), std::end(t),	//���������� ����������� ������� sort()� ������ ������� ������� ��������� �� ������ � �����
		[](const auto& a, const auto& b) {	//� ������� ������-������� ��������� ���������
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
