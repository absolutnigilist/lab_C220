#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <cstdlib>

class Writer {
	public:
		std::shared_ptr<std::ofstream> file;
		
		Writer(std::shared_ptr<std::ofstream> _file) :file(_file) {}
		void write(const std::string& message) {
			if (file&&file->is_open())
			{
				*file << message << std::endl;
			}
		}

};
void closeFile(std::ofstream* ofs) {
	if (ofs&&ofs->is_open())
	{
		ofs->close();
		std::cout << "File closed" << std::endl;
	}
	delete ofs;
}