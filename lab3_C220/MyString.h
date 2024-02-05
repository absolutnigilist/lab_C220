#pragma once

#pragma once
#include <iostream>
#include <string.h>

class MyString {
	char* p_Name;

public:
	MyString();
	MyString(const char* string);
	~MyString();
	MyString(const MyString& other);
	MyString(MyString&& other);
	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other);
	MyString& operator=(const char* other_string);
	friend std::ostream& operator<<(std::ostream& os, const MyString& other);
	const char* GetString()const;
	char& operator[](int index);
	const char& operator[](int index)const;
	void SetNewString(const char* newString);

};

