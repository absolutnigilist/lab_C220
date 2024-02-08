#pragma once

template<typename T>
void Print(const T& t) {
	for (const auto& val:t) {
		std::cout << *(val)<<' ';
	}
	std::cout << std::endl;
}
template<>
void Print(const std::vector<std::unique_ptr<std::string>>& str) {
	for (const auto& ptr : str) {
		std::cout << *(ptr)<<' ';
	}
	std::cout << std::endl;
}
void Modify(std::vector<std::unique_ptr<std::string>>& str,const std::string& suffix ){
	for (const auto& ptr : str) {
		*ptr += suffix;
	}
}
struct Deleter {
	void operator()(std::string* const ptr[]) {
		for (size_t i = 0; i < 3; ++i)
		{
			delete ptr[i];
		}
	}
};