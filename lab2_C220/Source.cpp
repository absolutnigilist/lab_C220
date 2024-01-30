#include "MyClass.h"
#include "MyVector.h"

int main(){

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

myVector<int> my_Vector(-10, 10);
my_Vector.setLowerBound(2);
my_Vector.add({ 1,15,-2,2,14,3,6,5,10,7 });
my_Vector.sort([](int a, int b) {return a < b; });
my_Vector.del({ 3,7 });
size_t size_vec=my_Vector.size();
bool if_find_vec=my_Vector.contains(5);
size_t index_vec = my_Vector[1];

std::vector<int> vec1;
std::copy(my_Vector.begin(), my_Vector.end(), std::back_inserter(vec1));
my_Vector.clear();
return 0;
}