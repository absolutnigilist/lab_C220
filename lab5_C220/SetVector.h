#pragma once

//лямбда-функция,заглушка-делетер
//позволяет избежать необходимости копирования строк и работать с исходными строками напрямую, не изменяя их порядок в массиве.
auto noop_deleter = [](std::string*) {};

// Определяем сравнивающую функцию для умных указателей
auto compare = [](const std::shared_ptr<std::string>& a, const std::shared_ptr<std::string>& b) { return *a < *b; };