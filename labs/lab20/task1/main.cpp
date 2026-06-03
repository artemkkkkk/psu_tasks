#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif


using namespace std;

class Time {
private:
    uint8_t hours;
    uint8_t minutes;

    void normalize() {
        int total_minutes = hours * 60 + minutes;
        total_minutes = (total_minutes % 1440 + 1440) % 1440;
        hours = total_minutes / 60;
        minutes = total_minutes % 60;
    }

public:
    Time() : hours(0), minutes(0) {}

    Time(uint8_t h, uint8_t m) {
        if (h > 23 || m > 59) {
            throw invalid_argument("Ошибка: Неверное время! Часы должны быть 0-23, минуты 0-59.");
        }
        hours = h;
        minutes = m;
    }

    Time(const Time& other) : hours(other.hours), minutes(other.minutes) {}

    Time addMinutes(unsigned int mins) const {
        Time result = *this;
        result.minutes += mins;
        result.normalize();
        return result;
    }

    friend ostream& operator<<(ostream& os, const Time& t) {
        os << setfill('0') << setw(2) << (int)t.hours << ":"
           << setfill('0') << setw(2) << (int)t.minutes;
        return os;
    }
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    Time t1;
    cout << "1. Конструктор по умолчанию: " << t1 << " (ожидается 00:00)" << endl;

    Time t2(14, 30);
    cout << "2. Конструктор с параметрами (14, 30): " << t2 << " (ожидается 14:30)" << endl;

    Time t3 = t2;
    cout << "3. Конструктор копирования: " << t3 << " (ожидается 14:30)" << endl;

    cout << "4. Проверка некорректных данных (25, 70): ";
    try {
        Time t_invalid(25, 70);
        cout << "ОШИБКА: Исключение не было выброшено!" << endl;
    } catch (const invalid_argument& e) {
        cout << "УСПЕХ: Перехвачено исключение -> " << e.what() << endl;
    }

    Time t4(23, 45);
    Time t5 = t4.addMinutes(30);
    cout << "5. Добавление 30 минут к 23:45: " << t5 << " (ожидается 00:15)" << endl;

    Time t6 = t1.addMinutes(1500);
    cout << "6. Добавление 1500 минут к 00:00: " << t6 << " (ожидается 01:00)" << endl;

    return 0;
}