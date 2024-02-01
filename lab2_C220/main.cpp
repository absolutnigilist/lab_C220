#include "MyClass.h"
#include "MyVector.h"
#include "MyUniquePTR.h"
#include "MyString.h"
#include <list>

int main(){
MyClass<int> def{};
MyClass<int> my_Class(-10, 10);											//создаем объект класса с границами значений
my_Class.setLowerBound(2);												//изменяем границу
my_Class.add({ 1,15,-2,2,14,3,6,5,10,7 });								//добавляем значения в вектор класса
my_Class.sort([](int a, int b) {return a < b; });						//с помощью шаблонного метода и лямбда-функции в качестве параметра сортируем по ВОЗРАСТАНИЮ
my_Class.sort([](int a, int b) {return a > b; });						//с помощью шаблонного метода и лямбда-функции в качестве параметра сортируем по УБЫВАНИЮ
my_Class.sort([](int a, int b) {return std::abs(a) < std::abs(b); });	//сортируем по модулю
my_Class.del({ 3,7 });													//удаляем знаяения в векторе класса
size_t size=my_Class.size();											//размер вектора
bool if_find = my_Class.contains(5);									//ищем заданное значение в векторе
size_t index = my_Class[1];												//второй элемент вектора

std::vector<int> vec;													//создаем пустой вектор
std::copy(my_Class.begin(), my_Class.end(), std::back_inserter(vec));	//копируем содержимое вектора my_Class во вторичный вектор
my_Class.clear();														//очищаем вектор

MyVector<int> my_Vector(-10, 10);										//инициализируем границы значений
my_Vector.setLowerBound(2);												//изменяем границу
my_Vector.add({ 1,15,-2,2,14,3,6,5,10,7 });								//добавляем значения в вектор 
my_Vector.sort();
my_Vector.sort([](int a, int b) {return a < b; });						//с помощью шаблонного метода и лямбда-функции в качестве параметра сортируем по ВОЗРАСТАНИЮ
my_Vector.del({ 3,7 });													//удаляем значения
size_t size_vec=my_Vector.size();										//размер вектора
bool if_find_vec=my_Vector.contains(5);									//ищем заданное значение в векторе
size_t index_vec = my_Vector[1];										//второй элемент вектора

std::vector<int> vec1;													//создаем пустой вектор
std::copy(my_Vector.begin(), my_Vector.end(), std::back_inserter(vec1));//копируем содержимое вектора my_Class во вторичный вектор
my_Vector.clear();														//очищаем вектор

MyUniquePTR<MyString> p1(new MyString("abc"));
std::cout << p1->GetString();
p1->SetNewString("qwerty");
MyString s2 = *p1;
//MyUniquePTR< MyString > p2=p1;										//здесь компилятор выдавает ошибку, так как мы запретили копирование
MyUniquePTR<MyString> p2 = std::move(p1);								//корректируем с помощью перемещающего конструктора копирования

if (!p1)																//т.к. владелец должен быть уникален, указатель содержит ноль
{ 
	std::cout << "No object!" << std::endl;  //а это должно работать
} 
MyUniquePTR< MyString > p3(new MyString("vvv"));
//p3 = p2;																//и здесь компилятор выдает ошибку, так как мы запретили присваивание
p3 = std::move(p2);														//копируем с помощью перемещающего оператора присваивания

std::vector<MyUniquePTR<MyString>> v;									//как проинициализировать?
v.emplace_back(new MyString("emplace"));					
v.push_back(MyUniquePTR<MyString>(new MyString("push_back")));

std::list<MyUniquePTR<MyString>> l;
for (auto& ptr : v) {
	l.push_back(std::move(ptr)); 
}

return 0;
}