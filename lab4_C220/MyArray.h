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
//��� ������� �������� ���������� ���������, ������������� � �������������� deduction guide (����������� �� ������ �����) ��� ������ MyArray.
//������ ������������� ��������� ��������� ������ MyArray<T, size> �� ������ �� ������� ������ ���� T �������� size.
template<typename T, size_t size>
MyArray(T(&)[size]) -> MyArray<T, size>;

//������ ������������� ��������� ��������� ������ MyArray<T, size> �� ����������� ������ �� ������� ������ ���� T �������� size.
template<typename T, size_t size>
MyArray(const T(&)[size]) -> MyArray<T, size>;
