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
	size_t count;
	Deleter(size_t _count = 0) :count(_count) {}
	void operator()(std::string* const ptr[]) {
		for (size_t i = 0; i < count; ++i)
		{
			delete ptr[i];
		}
	}
};