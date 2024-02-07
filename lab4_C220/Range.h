#pragma once
template<typename T>
class Range {
private:
    T minVal;
    T maxVal;

public:
    // ����������� ��� ������������� ������������ � ������������� ��������
    constexpr Range(T minVal, T maxVal) : minVal(minVal), maxVal(maxVal) {}

    // ������ ��� ��������� ������������ � ������������� ��������
    constexpr T getMin() const { return minVal; }
    constexpr T getMax() const { return maxVal; }

    // ����� ��� ��������, �������� �� ��������� �������� � ��������
    constexpr bool contains(T value) const {
        return value >= minVal && value <= maxVal;
    }

    // ����� ��� ������������ ��������������� ��������
    constexpr T clamp(T value) const {
        if (value < minVal) return minVal;
        if (value > maxVal) return maxVal;
        return value;
    }
};
