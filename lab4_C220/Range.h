#pragma once
template<typename T>
class Range {
private:
    T minVal;
    T maxVal;

public:
    //  онструктор дл€ инициализации минимального и максимального значений
    constexpr Range(T minVal, T maxVal) : minVal(minVal), maxVal(maxVal) {}

    // ћетоды дл€ получени€ минимального и максимального значений
    constexpr T getMin() const { return minVal; }
    constexpr T getMax() const { return maxVal; }

    // ћетод дл€ проверки, попадает ли указанное значение в диапазон
    constexpr bool contains(T value) const {
        return value >= minVal && value <= maxVal;
    }

    // ћетод дл€ формировани€ результирующего значени€
    constexpr T clamp(T value) const {
        if (value < minVal) return minVal;
        if (value > maxVal) return maxVal;
        return value;
    }
};
