#pragma once
constexpr int factorial(int val) {
	return val <= 1 ? 1 : factorial(val - 1);
}
/*  Ключевое слово constexpr указывает, что функция может быть вычислена на этапе компиляции,
	если аргументы функции являются константными выражениями.
	Цикл for выполняется до тех пор, пока символ в binary[i] не равен нулевому символу '\0', что означает конец строки.
	Внутри цикла происходит вычисление значения двоичного представления.
	При каждой итерации выполняется сдвиг result на один бит влево (result << 1),
	чтобы освободить место для нового бита.
	Затем к результату прибавляется значение текущего бита, вычисленное как разность binary[i] - '0'.
	Здесь символ '0' вычитается из binary[i], чтобы преобразовать символ в цифру.
	*/
constexpr int binaryLiteralToValue(const char* binary)
{
	int result = 0;

	// Вычисление значения двоичного представления
	for (int i = 0; binary[i] != '\0'; i++)
	{
		result = (result << 1) + (binary[i] - '0');
	}

	return result;
}
	
	constexpr int operator"" _b(const char* binary){	//Определение пользовательского литерала
	
		return binaryLiteralToValue(binary);
	}

	std::string toBinStr(unsigned int value) {
		if (value == 0) return "0b0";

		std::string result;
		while (value > 0) {
			// Добавляем '0' или '1' в начало строки в зависимости от последнего бита value
			result = (value % 2 == 0 ? "0" : "1") + result;
			value /= 2; // Сдвигаем значение на один бит вправо
		}
		result = "0b" + result; // Добавляем префикс "0b" в начало строки
		return result;
	}
	
	template<typename T>
	void printValue(const T& value) {
		if constexpr (std::is_pointer_v<T>) {
			if (value == nullptr) {
				std::cout << "null ";
			}
			else {
				std::cout << *value << " "; // Разыменовываем указатель, если это указатель
			}
		}
		else 
		{
			std::cout << value << " "; // Напрямую выводим значение, если это не указатель
		}
	}

	// Шаблонная функция для печати последовательностей
	template<typename Sequence>
	void PrintSequence(const Sequence& seq) {

		for (const auto& elem : seq) {
			printValue(elem); // Вызываем функцию для печати значения каждого элемента
		}
		std::cout << std::endl;
	}
	template<typename T, typename U>
	auto Add(T a, U b) {
		// Проверяем, является ли T вектором
		if constexpr (std::is_same_v<T, std::vector<U>>) {
			// Если да, проверяем, совпадают ли типы элементов вектора и второго параметра
			for (auto& item : a) {
				item += b;
			}
			return a;
		}
		else {
			// В противном случае просто складываем два значения
			return a + b;
		}
	}
	struct Comparator {
		bool operator()(int a, int b) {
			return a < b;
		}
	};

	
	template <typename T>
	void PrintAdapter(T& adapter) {
		if constexpr (std::is_same_v<T, std::stack<typename T::value_type, typename T::container_type>>|| std::is_same_v<T, std::priority_queue<typename T::value_type, typename T::container_type, std::less<typename T::value_type>>>) {
			while (!adapter.empty()) {
				if constexpr (std::is_pointer_v<typename T::value_type>) {
					std::cout << *(adapter.top()) << " ";
				}
				else {
					std::cout << adapter.top() << " ";
				}
				adapter.pop();
			}
		}
		/*else if constexpr (std::is_same_v<T, std::priority_queue<typename T::value_type, typename T::container_type, std::less<typename T::value_type>>>)
		{
			while (!adapter.empty()) {
				if constexpr (std::is_pointer_v<typename T::value_type>) {
					std::cout << *(adapter.top()) << " ";
				}
				else {
					std::cout << adapter.top() << " ";
				}
				adapter.pop();
			}
		}*/
		else if constexpr (std::is_same_v<T, std::queue<typename T::value_type, typename T::container_type>>) {
			while (!adapter.empty()) {
				if constexpr (std::is_pointer_v<typename T::value_type>) {
					std::cout << *(adapter.front()) << " ";
				}
				else {
					std::cout << adapter.front() << " ";
				}
				adapter.pop();
			}
		}
		std::cout << '\n';
	}

	template<typename T>
	constexpr auto Smth() {
		if constexpr (std::is_same<T, int>::value)
		{
			return 1;
		}
		else if constexpr (std::is_same<T, double>::value)
		{
			return 1.1;
		}
		else if constexpr (std::is_same<T, const char*>::value)
		{
			return "abc";
		}
		else
		{
			return T{};
		}
			
	}