#define _CRT_SECURE_NO_WARNINGS
#include"MyString.h"


MyString::MyString() {
	p_Name = nullptr;
}
MyString::MyString(const char* string_other) {
	p_Name = new char[strlen(string_other) + 1];
	strcpy(p_Name, string_other);
}
MyString::~MyString() {
	if (p_Name)
	{
		delete[]p_Name;
		p_Name = nullptr;
	}
}
MyString::MyString(const MyString& other) {
	if (other.p_Name != nullptr)
	{
		p_Name = new char[strlen(other.p_Name) + 1];
		strcpy(p_Name, other.p_Name);
	}
	else
	{
		p_Name = nullptr;
	}
}
MyString::MyString(MyString&& other) {
	p_Name = other.p_Name;
	other.p_Name = nullptr;
}
MyString& MyString::operator=(const MyString& other) {
	if (this != &other)
	{
		delete[]p_Name;
		if (other.p_Name != nullptr)
		{
			p_Name = new char[strlen(other.p_Name) + 1];
			strcpy(p_Name, other.p_Name);
		}
		else
		{
			p_Name = nullptr;
		}
	}
	return *this;
}
MyString& MyString::operator=(MyString&& other) {
	if (this != &other)
	{
		delete[]p_Name;
		p_Name = other.p_Name;
		other.p_Name = nullptr;
	}
	return *this;
}
MyString& MyString::operator=(const char* other_string) {
	if (p_Name != other_string)
	{
		delete[]p_Name;
		p_Name = new char[strlen(other_string) + 1];
		strcpy(p_Name, other_string);
	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const MyString& other) {
	os << other.p_Name;
	return os;
}
const char* MyString::GetString()const {
	return p_Name;
}
char& MyString::operator[](int index)
{
	if (index >= 0 && index <= strlen(p_Name))
	{
		return p_Name[index];
	}
	else
	{
		throw std::out_of_range("Index out of range");
	}
}
const char& MyString::operator[](int index) const
{
	if (index >= 0 && index < strlen(p_Name))
	{
		return p_Name[index];
	}
}
void MyString::SetNewString(const char* newString) {
	if (p_Name) delete[] p_Name;								// Освобождаем старую строку
	if (newString) {
		p_Name = new char[std::strlen(newString) + 1];
		std::strcpy(p_Name, newString);							// Копируем новую строку
	}
	else {
		p_Name = nullptr;
	}
}
