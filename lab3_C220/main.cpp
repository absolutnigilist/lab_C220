#include "Header.h"
#include "MyString.h"

int main() {
	MyQueue<MyString>  q1{ MyString("AAA"), MyString("qwerty"),MyString("WWW")};
	

	//использование MyQueue в диапазонном for:
	for (const auto& el : q1) { std::cout << el << ' '; } std::cout<< std::endl;

	MyString s("abc");
	q1.push(s);
	Print(q1);
	q1.push(MyString("123"));
	Print(q1);
	MyString s1 = q1.pop();
	q1.push("qqq");
	Print(q1);
	MyQueue < MyString >  q2 = q1;
	Print(q2);
	//MyQueue < MyString >  q22 = std::move(q1);
	//Print(q22);
	
	/*try {
		q22.resize(2);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Caught an std::invalid_argument: " << e.what() << std::endl;
	}*/

	MyQueue < MyString >  q3{ 10, MyString("!")}; //очередь должна содержать 10 элементов со строкой «!» 
	Print(q3);
	q3 = q1;
	Print(q1);
	Print(q3);
	q2 = MyQueue < MyString >(5, MyString("?"));
	Print(q2);
	q1 = { MyString("bbb"), MyString("ssss")};
	Print(q1);


	return 0;
}