#pragma once
template <typename T>
class MyUniquePTR {
private:
    T* pointer;                                                             // Указатель на управляемый объект

public:
    explicit MyUniquePTR(T* ptr = nullptr) : pointer(ptr) {}                 // Конструктор
    ~MyUniquePTR() {                                                         // Деструктор
        delete pointer;
    }
    MyUniquePTR(const MyUniquePTR&) = delete;                               // Запрещаем копирование
    MyUniquePTR& operator=(const MyUniquePTR&) = delete;                    // Запрещаем присваивание
    MyUniquePTR(MyUniquePTR&& moving) noexcept: pointer(moving.pointer) { // Реализация перемещения
        moving.pointer = nullptr;
    }
    MyUniquePTR& operator=(MyUniquePTR&& moving) noexcept {
        if (this != &moving) {
            delete pointer; // Освобождаем старый ресурс
            pointer = moving.pointer;
            moving.pointer = nullptr;
        }
        return *this;
    }
    T& operator*() const {                                                  // Оператор разыменования
        return *pointer;
    }
    T* operator->() const {                                                  // Оператор доступа к члену класса
        return pointer;
    }
    operator bool()const {
        return pointer != nullptr;                                          //проверка, есть ли в указателе объект
    }
};