#pragma once
#include <iostream>
#include <list>

template<typename T>
void PrintAnyCont(T& t) {
	for (const auto& cont : t) {
		std::cout << cont << ", ";
	}
	std::cout << std::endl;
}

template<typename T>
void NegateAll(T& t) {
	for (auto& val : t) {
		val = -val;
	}
}
template<>
void NegateAll(std::list<std::string>& ls) {
	for (auto& str : ls) {
		for (auto& ch : str) {
			if (std::isalpha(ch))
			{
				ch = std::isupper(ch) ? std::tolower(ch) : std::toupper(ch);
			}
		}
	}
}
