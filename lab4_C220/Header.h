#pragma once
constexpr int factorial(int val) {
	return val <= 1 ? 1 : factorial(val - 1);
}
/*  �������� ����� constexpr ���������, ��� ������� ����� ���� ��������� �� ����� ����������,
	���� ��������� ������� �������� ������������ �����������.
	���� for ����������� �� ��� ���, ���� ������ � binary[i] �� ����� �������� ������� '\0', ��� �������� ����� ������.
	������ ����� ���������� ���������� �������� ��������� �������������.
	��� ������ �������� ����������� ����� result �� ���� ��� ����� (result << 1),
	����� ���������� ����� ��� ������ ����.
	����� � ���������� ������������ �������� �������� ����, ����������� ��� �������� binary[i] - '0'.
	����� ������ '0' ���������� �� binary[i], ����� ������������� ������ � �����.
	*/
constexpr int binaryLiteralToValue(const char* binary)
{
	int result = 0;

	// ���������� �������� ��������� �������������
	for (int i = 0; binary[i] != '\0'; i++)
	{
		result = (result << 1) + (binary[i] - '0');
	}

	return result;
}
	
	constexpr int operator"" _b(const char* binary){	//����������� ����������������� ��������
	
		return binaryLiteralToValue(binary);
	}

	std::string toBinStr(unsigned int value) {
		if (value == 0) return "0b0";

		std::string result;
		while (value > 0) {
			// ��������� '0' ��� '1' � ������ ������ � ����������� �� ���������� ���� value
			result = (value % 2 == 0 ? "0" : "1") + result;
			value /= 2; // �������� �������� �� ���� ��� ������
		}
		result = "0b" + result; // ��������� ������� "0b" � ������ ������
		return result;
	}
	
	template<typename T>
	void printValue(const T& value) {
		if constexpr (std::is_pointer_v<T>) {
			if (value == nullptr) {
				std::cout << "null ";
			}
			else {
				std::cout << *value << " "; // �������������� ���������, ���� ��� ���������
			}
		}
		else 
		{
			std::cout << value << " "; // �������� ������� ��������, ���� ��� �� ���������
		}
	}

	// ��������� ������� ��� ������ �������������������
	template<typename Sequence>
	void PrintSequence(const Sequence& seq) {

		for (const auto& elem : seq) {
			printValue(elem); // �������� ������� ��� ������ �������� ������� ��������
		}
		std::cout << std::endl;
	}
	template<typename T, typename U>
	auto Add(T a, U b) {
		// ���������, �������� �� T ��������
		if constexpr (std::is_same_v<T, std::vector<U>>) {
			// ���� ��, ���������, ��������� �� ���� ��������� ������� � ������� ���������
			for (auto& item : a) {
				item += b;
			}
			return a;
		}
		else {
			// � ��������� ������ ������ ���������� ��� ��������
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