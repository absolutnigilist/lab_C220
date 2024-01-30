#pragma once
#include<vector>

template<typename T>
class MyClass {
	std::vector<T> data;
	T lower_bound, upper_bound;

	bool isValid(const T& value) {
		return(value >= this->lower_bound && value <= this->upper_bound);
	}
public:
	MyClass(T lower, T upper) :lower_bound(lower), upper_bound(upper) {};
	void add(const std::initializer_list<T>& list) {
		for (const auto& val : list) {
			if (isValid(val) && std::find(data.begin(), data.end(), val) == data.end()) {
				data.push_back(val);
			}
		}
	}
	void del(const std::initializer_list<T>& list) {
		for (const auto& val : list) {
			auto it = std::find(data.begin(), data.end(), val);
			if (it != data.end()) {
				data.erase(it);
			}
		}
	}

};