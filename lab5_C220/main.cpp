#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <string>
#include "Header.h"
#include "Writer.h"
#include "SetVector.h"
#include "Human.h"


int main()
{
	setlocale(LC_ALL, "Russian");
	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 1. unique_ptr
	{

		{//1.� - ���������� ���������� ���������� ���������
		
			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
			
			//������������ ��� ������
			Print(v);

			//����������� ����������� ����������� ������
			for (const auto& ptr : v) {
				delete ptr;
			}
			__asm nop
		}

		{//1.b - ������������� ������� 1.�:
		 //���������� ����������� std::unique_ptr: 
		 //����������� ���������� (��������� ��� ������ ������� ������������ std::unique_ptr), 
		 //���������� �������� ���������� �� ����������� ����������� ������� std::string, 
		 //���������������,� ������������ ��������

		
			std::vector<std::unique_ptr<std::string>> v;

			v.push_back(std::make_unique<std::string>("aa"));
			v.push_back(std::make_unique<std::string>("bb"));
			v.push_back(std::make_unique<std::string>("cc"));
			
			//������������ ��� ������
			
			Print(v);
			if (!v.empty())
			{
				//������������ ������ ������
				*v[0] = "aa_modified";
			}

			Print(v);

			// ����������� ����������� ��������� �������� ���������� ������������� ��� ������ �� ������� ���������
			__asm nop
		}

		{//1.c - ��������� ������� 1.b �������� ����������� �������� ���������� ������
		 //��������� ������� (��������, �������� ��������� �������: "AAA" -> "AAA_1")  
			
			std::vector<std::unique_ptr<std::string>> v;

			v.push_back(std::make_unique<std::string>("aa"));
			v.push_back(std::make_unique<std::string>("bb"));
			v.push_back(std::make_unique<std::string>("cc"));

			Modify(v, "_1");
			Print(v);

			__asm nop
		}

		{//1.d - ������������ ������ ��������	

		 //�������� unique_ptr, ������� �������� �������� ��� ������������� �������
		 //� ���������� std::string
		 //� ������� unique_ptr::operator[] ��������� ��������� ������ ����������
		 //����� ���������� ������������ ������?

			std::unique_ptr<std::string[]> ptr(new std::string[3]);
			ptr[0]="aa";
			ptr[1] = "bb";
			ptr[2] = "cc";
			
			__asm nop
			// ������������ ������ ���������� ������������� ��� ������ �� ������� ���������
		}

		{//1.e - ������� ������������ �������� � ���������������� delete-������� (�������)
		 //����� �������� ������ ���������� �� ����������� ��������� �������
		 //�������� unique_ptr ��� ������ �������
		 //���������� ���������������� delete-������� (�������) ��� ����������� 
		 //������������ ������

			std::string* arStrPtr[] = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
			std::unique_ptr<std::string* [], Deleter> ptr(arStrPtr, Deleter());
			
			__asm nop
			// ������������ ������ � �������������� ����������������� ��������
		}

		{//1.f �������� � ��������� ������, ���������� unique_ptr ��� ���������� �� std::string
			//����������� ��������� copy() ���������� �������� ������� � ������ ������ � ���������� 
			//���� �� ����
			//���������: ������������ ��������� � ������ std::make_move_iterator

			std::vector<std::unique_ptr<std::string>> vec;
			vec.push_back(std::make_unique<std::string>("aa"));
			vec.push_back(std::make_unique<std::string>("bb"));
			vec.push_back(std::make_unique<std::string>("cc"));

			std::list<std::unique_ptr<std::string>> ls;
			std::copy(std::make_move_iterator(vec.begin()), std::make_move_iterator(vec.end()), std::back_inserter(ls));
			
			__asm nop
			// ������ ������ ������, � ������ �������� ��� ��������
		}
		

	}

	////////////////////////////////////////////////////////////////////////////////
	//������� 2.shared_ptr + ���������������� delete-������� 

	//����������� ����������� ������ � ���� ������ (�������) �� ������ ���������� 
	//��� ��� ��� "��������" ����� �� ������� ���������� ���� ������ � ���� � ��� �� ����,
	//������� ������������ �� ����������� ������������ ����� � ��� �� �������� ������ ������ =>
	//���������� �������� ��� ������ ��������� �������� shared_ptr
	//�. ������ �������� ������ �������/������� ���� ��� ������
	//�. ��� ��������� �������� ������ �������������� � �������������
	//�. ��������� �������� ��������� ������ ������� ����

	//���������: ����������� ������� ������ ����� � ������� ������� rand()
	
	{

	// �������� ����� ��� ������ � �������� shared_ptr � ���������������� delete-��������
	
	auto file = std::shared_ptr < std::ofstream>(new std::ofstream("example.txt", std::ios::out), closeFile);

	// ������� ���� "���������"

	Writer writer1(file), writer2(file);

	// ������ ������ � ����
	//�������� ����� �������� ��������� ������� ��������� ������ �� "���������" �������� � ����
	//���� �������

	const int iterations = 10; // ���������� �������� ������
	for (int i = 0; i < iterations; ++i) {
		if (rand() % 2 == 0) {
			writer1.write("Writer 1: Line " + std::to_string(i));
		}
		else {
			writer2.write("Writer 2: Line " + std::to_string(i));
		}
	}

	// ����� ������ �� ������� ��������� ���������� shared_ptr, ���� ������������� ���������
	__asm nop
	}
	//������� 3.
	{
		//��� ������ ��������� ���� string
		std::string strings[] = { "abc", "123", "qwerty", "#$%" };

		//�� ���������� ��������� ������ ������ ������������ � ������������ ����������.
		//��������� ���������� ��������������� �������� �) ��� ����������� � �) ��� ��������� �������
		//��������� � �������!
		// ������� ��������� � ������� ��� �������� ����� ���������� �� ������

		std::set<std::shared_ptr<std::string>, decltype(compare)> letterStrings(compare);
		std::vector<std::shared_ptr<std::string>> digitStrings;
		std::vector<std::shared_ptr<std::string>> nonAlphanumericStrings;

		for (auto& s : strings) {
			bool onlyDigits = true;
			bool onlyLetters = true;
			for (auto& c:s) {
				if (!std::isdigit(c))
				{
					onlyDigits = false;
				}
				if (!std::isalpha(c))
				{
					onlyLetters = false;
				}
			}
			if (onlyLetters)
			{
				//� set "����������" �� �������� ������� ��� �����, ������� �������� ������ ����� 
				letterStrings.insert(std::shared_ptr<std::string>(&s, noop_deleter));
			}
			else if (onlyDigits)
			{
				//� std::vector "����������" ������� ��� �����, ������� �������� ������ �����
				digitStrings.push_back(std::shared_ptr<std::string>(&s, noop_deleter));
			}
			else
			{
				//���� "����������" ������� ��� �����, ������� �� �������� �� �������� ����, �� �������� ����
				nonAlphanumericStrings.push_back(std::shared_ptr<std::string>(&s, noop_deleter));
			}
		}
	
		/******************************************************************************************/
		//������� �� �����
		//������� ����� ������� ��� ������ �����
		
		int sum = 0;
		for (const auto& ptr : digitStrings) {
			std::cout << *ptr << "\n";
			sum += std::atoi(ptr->c_str());
		}
		std::cout << "�����: " << sum << "\n";
		
		/******************************************************************************************/
		
		//������� ������, ��� ��� ���� � ����

		for (const auto& ptr : nonAlphanumericStrings) {
			std::cout << *ptr << "\n";
		}

		/******************************************************************************************/

		//������� ������ � ������� �� �����

		for (const auto& ptr : letterStrings) {
			std::cout << *ptr << "\n";
		}
		__asm nop
	}
	/******************************************************************************************/
		//������� 4. 
	{
		//����:
		std::string ar[] = { "my","Hello", "World" };
		std::vector < std::shared_ptr<std::string>> v = { std::make_shared<std::string>("good"), std::make_shared<std::string>("bye") };



		//�) ��������� �������� � ������ ������� ��� ��������� �������, �� ������� �������� �������!
		for (auto& s : ar) {
			v.push_back(std::shared_ptr<std::string>(&s, noop_deleter));
		}
		//�) ������������� ������ �� �������� � ������� �� �����
		
		Print(v);
		std::sort(v.begin(), v.end(), compare);
		std::cout << "��������������� ������:" << std::endl;
		Print(v);


		//�) ���������� ���������� ������������ ������
		//������������ ������ ��� ���������, ����������� ����� std::make_shared, ���������� �������������

		__asm nop
	}
	/***************************************************************/

	//������� 5. shared_ptr � weak_ptr
		//������� ��������������� ������ ����������� ������ human. � ������ ��������:
		//��� - string
		//�������� �������: ��� ��� ��� ���...
		//�������� - shared_ptr (�������� �� ������ ��������...)
		//���� - ��������� �� weak_ptr (����� �������� ����������� ������������)

		//������ ������ human:
		//����������� - ��� ������������� ����� � ��������
		//����������� �����������, �������� ������������, move ???
		//����������� ����� child() - 
		//				������ ������� ������� � ������� ������� ��� ����������� ��������
		//				+ ������������ ��� ����� ������� � ���������� � ��������

		//������ ����������� ����������� ��������������� ������ ��� ���������� ����������

	{
		//������� ������ � ����-�� ���������� => "����-���� ��� �� ����, ��������, ���� � ���"
		//(�� ���� �� ����� ���� ��� ���� � ��� ����):
		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...
		//� ��� ��������� ���� - child():
		//� � ����� � ���� ������� ���� ����:


		auto eve = std::make_shared<Human>("Eve");
		auto adam = std::make_shared<Human>("Adam");

		auto cain = Human::child("Cain", eve, adam);
		auto abel = Human::child("Abel", eve, adam);

		auto enoch = Human::child("Enoch", cain, nullptr); // ������, ����� �������� ������ ���� ��������

		std::cout << "Family tree for Eve:" << std::endl;
		eve->printFamilyTree();

		std::cout << "\nFamily tree for Adam:" << std::endl;
		adam->printFamilyTree();
		
		__asm nop
	}

	return 0;

}