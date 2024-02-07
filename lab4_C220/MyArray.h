#pragma once
template<typename T, size_t size>
class MyArray
{
	T ar[size]{};

public:
	constexpr MyArray() = default;

	constexpr MyArray(const T* data) {
		for (size_t i = 0; i < size; ++i) {
			ar[i] = data[i];
		}
	}
};
//Эти функции являются шаблонными функциями, определенными с использованием deduction guide (руководства по выводу типов) для класса MyArray.
//Первая специализация позволяет создавать объект MyArray<T, size> из ссылки на обычный массив типа T размером size.
template<typename T, size_t size>
MyArray(T(&)[size]) -> MyArray<T, size>;

//Вторая специализация позволяет создавать объект MyArray<T, size> из константной ссылки на обычный массив типа T размером size.
template<typename T, size_t size>
MyArray(const T(&)[size]) -> MyArray<T, size>;
