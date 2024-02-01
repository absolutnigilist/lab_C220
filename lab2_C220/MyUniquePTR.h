#pragma once
template <typename T>
class MyUniquePTR {
private:
    T* pointer;                                                             // ��������� �� ����������� ������

public:
    explicit MyUniquePTR(T* ptr = nullptr) : pointer(ptr) {}                 // �����������
    ~MyUniquePTR() {                                                         // ����������
        delete pointer;
    }
    MyUniquePTR(const MyUniquePTR&) = delete;                               // ��������� �����������
    MyUniquePTR& operator=(const MyUniquePTR&) = delete;                    // ��������� ������������
    MyUniquePTR(MyUniquePTR&& moving) noexcept: pointer(moving.pointer) { // ���������� �����������
        moving.pointer = nullptr;
    }
    MyUniquePTR& operator=(MyUniquePTR&& moving) noexcept {
        if (this != &moving) {
            delete pointer; // ����������� ������ ������
            pointer = moving.pointer;
            moving.pointer = nullptr;
        }
        return *this;
    }
    T& operator*() const {                                                  // �������� �������������
        return *pointer;
    }
    T* operator->() const {                                                  // �������� ������� � ����� ������
        return pointer;
    }
    operator bool()const {
        return pointer != nullptr;                                          //��������, ���� �� � ��������� ������
    }
};