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
	//Задание 1. unique_ptr
	{

		{//1.а - обеспечьте корректное выполнение фрагмента
		
			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
			
			//Распечатайте все строки
			Print(v);

			//освобождаем динамически захваченную память
			for (const auto& ptr : v) {
				delete ptr;
			}
			__asm nop
		}

		{//1.b - модифицируйте задание 1.а:
		 //обеспечьте посредством std::unique_ptr: 
		 //эффективное заполнение (вспомните про разные способы формирования std::unique_ptr), 
		 //безопасное хранение указателей на динамически создаваемые объекты std::string, 
		 //манипулирование,и освобождение ресурсов

		
			std::vector<std::unique_ptr<std::string>> v;

			v.push_back(std::make_unique<std::string>("aa"));
			v.push_back(std::make_unique<std::string>("bb"));
			v.push_back(std::make_unique<std::string>("cc"));
			
			//Распечатайте все строки
			
			Print(v);
			if (!v.empty())
			{
				//модифицируем первую строку
				*v[0] = "aa_modified";
			}

			Print(v);

			// Уничтожение динамически созданных объектов произойдет автоматически при выходе из области видимости
			__asm nop
		}

		{//1.c - дополните задание 1.b добавьте возможность изменять хранящиеся строки
		 //следующим образом (например, добавить указанный суффикс: "AAA" -> "AAA_1")  
			
			std::vector<std::unique_ptr<std::string>> v;

			v.push_back(std::make_unique<std::string>("aa"));
			v.push_back(std::make_unique<std::string>("bb"));
			v.push_back(std::make_unique<std::string>("cc"));

			Modify(v, "_1");
			Print(v);

			__asm nop
		}

		{//1.d - динамический массив объектов	

		 //Создайте unique_ptr, который является оберткой для динамического массива
		 //с элементами std::string
		 //С помощью unique_ptr::operator[] заполните обернутый массив значениями
		 //Когда происходит освобождения памяти?

			std::unique_ptr<std::string[]> ptr(new std::string[3]);
			ptr[0]="aa";
			ptr[1] = "bb";
			ptr[2] = "cc";
			
			__asm nop
			// Освобождение памяти происходит автоматически при выходе из области видимости
		}

		{//1.e - массивы динамических объектов и пользовательская delete-функция (функтор)
		 //Задан стековый массив указателей на динамически созданные объекты
		 //Создайте unique_ptr для такого массива
		 //Реализуйте пользовательскую delete-функцию (функтор) для корректного 
		 //освобождения памяти

			std::string* arStrPtr[] = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
			std::unique_ptr<std::string* [], Deleter> ptr(arStrPtr, Deleter());
			
			__asm nop
			// Освобождение памяти с использованием пользовательского делетера
		}

		{//1.f Создайте и заполните вектор, содержащий unique_ptr для указателей на std::string
			//Посредством алгоритма copy() скопируйте элементы вектора в пустой список с элементами 
			//того же типа
			//Подсказка: перемещающие итераторы и шаблон std::make_move_iterator

			std::vector<std::unique_ptr<std::string>> vec;
			vec.push_back(std::make_unique<std::string>("aa"));
			vec.push_back(std::make_unique<std::string>("bb"));
			vec.push_back(std::make_unique<std::string>("cc"));

			std::list<std::unique_ptr<std::string>> ls;
			std::copy(std::make_move_iterator(vec.begin()), std::make_move_iterator(vec.end()), std::back_inserter(ls));
			
			__asm nop
			// Вектор теперь пустой, а список содержит все элементы
		}
		

	}

	////////////////////////////////////////////////////////////////////////////////
	//Задание 2.shared_ptr + пользовательская delete-функция 

	//Реализовать возможность записи в файл данных (строчек) из разных источников 
	//Так как все "писатели" будут по очереди записывать свои данные в один и тот же файл,
	//логично предоставить им возможность пользоваться одним и тем же объектом потока вывода =>
	//безопасной оберткой для такого указателя является shared_ptr
	//а. Первый владелец должен открыть/создать файл для записи
	//б. Все остальные писатели должны присоединиться к использованию
	//в. Последний владелец указателя должен закрыть файл

	//Подсказка: имитировать порядок записи можно с помощью функции rand()
	
	{

	// Открытие файла для записи и создание shared_ptr с пользовательской delete-функцией
	
	auto file = std::shared_ptr < std::ofstream>(new std::ofstream("example.txt", std::ios::out), closeFile);

	// Создаем двух "писателей"

	Writer writer1(file), writer2(file);

	// Запись данных в файл
	//заданное число итераций случайным образом позволяем одному из "писателей" записать в файл
	//свою строчку

	const int iterations = 10; // Количество итераций записи
	for (int i = 0; i < iterations; ++i) {
		if (rand() % 2 == 0) {
			writer1.write("Writer 1: Line " + std::to_string(i));
		}
		else {
			writer2.write("Writer 2: Line " + std::to_string(i));
		}
	}

	// После выхода из области видимости последнего shared_ptr, файл автоматически закроется
	__asm nop
	}
	//Задание 3.
	{
		//Дан массив элементов типа string
		std::string strings[] = { "abc", "123", "qwerty", "#$%" };

		//До завершения фрагмента строки должны существовать в единственном экземпляре.
		//Требуется обеспечить манипулирование строками а) без копирования и б) без изменения порядка
		//элементов в массиве!
		// Создаем множество и векторы для хранения умных указателей на строки

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
				//В set "складываем" по алфавиту обертки для строк, которые содержат только буквы 
				letterStrings.insert(std::shared_ptr<std::string>(&s, noop_deleter));
			}
			else if (onlyDigits)
			{
				//В std::vector "складываем" обертки для строк, которые содержат только цифры
				digitStrings.push_back(std::shared_ptr<std::string>(&s, noop_deleter));
			}
			else
			{
				//сюда "складываем" обертки для строк, которые не содержат ни символов букв, ни символов цифр
				nonAlphanumericStrings.push_back(std::shared_ptr<std::string>(&s, noop_deleter));
			}
		}
	
		/******************************************************************************************/
		//Выводим на экран
		//Находим сумму вектора где только цифры
		
		int sum = 0;
		for (const auto& ptr : digitStrings) {
			std::cout << *ptr << "\n";
			sum += std::atoi(ptr->c_str());
		}
		std::cout << "Сумма: " << sum << "\n";
		
		/******************************************************************************************/
		
		//Выводим вектор, где нет букв и цифр

		for (const auto& ptr : nonAlphanumericStrings) {
			std::cout << *ptr << "\n";
		}

		/******************************************************************************************/

		//Выводим строки с буквами на экран

		for (const auto& ptr : letterStrings) {
			std::cout << *ptr << "\n";
		}
		__asm nop
	}
	/******************************************************************************************/
		//Задание 4. 
	{
		//Дано:
		std::string ar[] = { "my","Hello", "World" };
		std::vector < std::shared_ptr<std::string>> v = { std::make_shared<std::string>("good"), std::make_shared<std::string>("bye") };



		//а) Требуется добавить в вектор обертки для элементов массива, НЕ копируя элементы массива!
		for (auto& s : ar) {
			v.push_back(std::shared_ptr<std::string>(&s, noop_deleter));
		}
		//б) Отсортировать вектор по алфавиту и вывести на экран
		
		Print(v);
		std::sort(v.begin(), v.end(), compare);
		std::cout << "Отсортированный вектор:" << std::endl;
		Print(v);


		//в) Обеспечить корректное освобождение памяти
		//Освобождение памяти для элементов, добавленных через std::make_shared, происходит автоматически

		__asm nop
	}
	/***************************************************************/

	//Задание 5. shared_ptr и weak_ptr
		//Создаем генеалогическое дерево посредством класса human. В классе хранятся:
		//имя - string
		//возможно признак: жив или уже нет...
		//родители - shared_ptr (родители не всегда известны...)
		//дети - контейнер из weak_ptr (чтобы избежать циклических зависимостей)

		//Методы класса human:
		//конструктор - для инициализации имени и признака
		//конструктор копирования, оператор присваивания, move ???
		//статический метод child() - 
		//				должен создать создать и вернуть обертку для родившегося человека
		//				+ сформировать все связи ребенка с родителями и наоборот

		//Ввести возможность распечатать генеалогическое дерево для указанного индивидума

	{
		//История должна с кого-то начинаться => "Жили-были дед да баба, например, Адам и Ева"
		//(то есть на самом деле два деда и две бабы):
		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...
		//у них появились дети - child():
		//а у детей в свою очередь свои дети:


		auto eve = std::make_shared<Human>("Eve");
		auto adam = std::make_shared<Human>("Adam");

		auto cain = Human::child("Cain", eve, adam);
		auto abel = Human::child("Abel", eve, adam);

		auto enoch = Human::child("Enoch", cain, nullptr); // Пример, когда известен только один родитель

		std::cout << "Family tree for Eve:" << std::endl;
		eve->printFamilyTree();

		std::cout << "\nFamily tree for Adam:" << std::endl;
		adam->printFamilyTree();
		
		__asm nop
	}

	return 0;

}