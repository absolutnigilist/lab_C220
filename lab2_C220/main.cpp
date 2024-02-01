#include "MyClass.h"
#include "MyVector.h"
#include "MyUniquePTR.h"
#include "MyString.h"
#include <list>

int main(){
MyClass<int> def{};
MyClass<int> my_Class(-10, 10);											//������� ������ ������ � ��������� ��������
my_Class.setLowerBound(2);												//�������� �������
my_Class.add({ 1,15,-2,2,14,3,6,5,10,7 });								//��������� �������� � ������ ������
my_Class.sort([](int a, int b) {return a < b; });						//� ������� ���������� ������ � ������-������� � �������� ��������� ��������� �� �����������
my_Class.sort([](int a, int b) {return a > b; });						//� ������� ���������� ������ � ������-������� � �������� ��������� ��������� �� ��������
my_Class.sort([](int a, int b) {return std::abs(a) < std::abs(b); });	//��������� �� ������
my_Class.del({ 3,7 });													//������� �������� � ������� ������
size_t size=my_Class.size();											//������ �������
bool if_find = my_Class.contains(5);									//���� �������� �������� � �������
size_t index = my_Class[1];												//������ ������� �������

std::vector<int> vec;													//������� ������ ������
std::copy(my_Class.begin(), my_Class.end(), std::back_inserter(vec));	//�������� ���������� ������� my_Class �� ��������� ������
my_Class.clear();														//������� ������

MyVector<int> my_Vector(-10, 10);										//�������������� ������� ��������
my_Vector.setLowerBound(2);												//�������� �������
my_Vector.add({ 1,15,-2,2,14,3,6,5,10,7 });								//��������� �������� � ������ 
my_Vector.sort();
my_Vector.sort([](int a, int b) {return a < b; });						//� ������� ���������� ������ � ������-������� � �������� ��������� ��������� �� �����������
my_Vector.del({ 3,7 });													//������� ��������
size_t size_vec=my_Vector.size();										//������ �������
bool if_find_vec=my_Vector.contains(5);									//���� �������� �������� � �������
size_t index_vec = my_Vector[1];										//������ ������� �������

std::vector<int> vec1;													//������� ������ ������
std::copy(my_Vector.begin(), my_Vector.end(), std::back_inserter(vec1));//�������� ���������� ������� my_Class �� ��������� ������
my_Vector.clear();														//������� ������

MyUniquePTR<MyString> p1(new MyString("abc"));
std::cout << p1->GetString();
p1->SetNewString("qwerty");
MyString s2 = *p1;
//MyUniquePTR< MyString > p2=p1;										//����� ���������� �������� ������, ��� ��� �� ��������� �����������
MyUniquePTR<MyString> p2 = std::move(p1);								//������������ � ������� ������������� ������������ �����������

if (!p1)																//�.�. �������� ������ ���� ��������, ��������� �������� ����
{ 
	std::cout << "No object!" << std::endl;  //� ��� ������ ��������
} 
MyUniquePTR< MyString > p3(new MyString("vvv"));
//p3 = p2;																//� ����� ���������� ������ ������, ��� ��� �� ��������� ������������
p3 = std::move(p2);														//�������� � ������� ������������� ��������� ������������

std::vector<MyUniquePTR<MyString>> v;									//��� �������������������?
v.emplace_back(new MyString("emplace"));					
v.push_back(MyUniquePTR<MyString>(new MyString("push_back")));

std::list<MyUniquePTR<MyString>> l;
for (auto& ptr : v) {
	l.push_back(std::move(ptr)); 
}

return 0;
}