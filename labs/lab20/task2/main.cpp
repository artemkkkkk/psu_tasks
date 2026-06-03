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
            throw invalid_argument("Ошибка: Неверное время! Часы 0-23, минуты 0-59.");
        }
        hours = h;
        minutes = m;
    }

    Time(const Time& other) : hours(other.hours), minutes(other.minutes) {}

    Time& operator++() {
        minutes++;
        normalize();
        return *this;
    }

    Time operator++(int) {
        Time temp = *this;
        ++(*this);
        return temp;
    }

    Time& operator--() {
        minutes--;
        normalize();
        return *this;
    }

    Time operator--(int) {
        Time temp = *this;
        --(*this);
        return temp;
    }

    explicit operator short int() const {
        return static_cast<short int>(hours);
    }

    operator bool() const {
        return (hours != 0 || minutes != 0);
    }

    Time operator+(const Time& t) const {
        Time result = *this;
        result.hours += t.hours;
        result.minutes += t.minutes;
        result.normalize();
        return result;
    }

    Time operator+(unsigned int mins) const {
        Time result = *this;
        result.minutes += mins;
        result.normalize();
        return result;
    }

    Time operator-(const Time& t) const {
        Time result = *this;
        result.hours -= t.hours;
        result.minutes -= t.minutes;
        result.normalize();
        return result;
    }

    Time operator-(unsigned int mins) const {
        Time result = *this;
        result.minutes -= mins;
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

    Time t1(10, 30);
    Time t2(2, 45);

    cout << "Исходные значения: t1 = " << t1 << ", t2 = " << t2 << endl;

    Time t3 = t1;
    ++t3;
    cout << "1. Префиксный ++t1 (10:30): " << t3 << " (ожидается 10:31)" << endl;

    Time t4 = t1;
    t4--;
    cout << "2. Постфиксный t1-- (10:30): " << t4 << " (ожидается 10:29)" << endl;

    Time t5(0, 0);
    --t5;
    cout << "3. Декремент 00:00 (переход в предыдущие сутки): " << t5 << " (ожидается 23:59)" << endl;

    short int h = static_cast<short int>(t1);
    cout << "4. Явное приведение к short int (t1): " << h << " (ожидается 10)" << endl;

    Time t_zero(0, 0);
    Time t_nonzero(0, 1);
    cout << "5. Неявное приведение к bool (00:00): " << (t_zero ? "true" : "false") << " (ожидается false)" << endl;
    cout << "6. Неявное приведение к bool (00:01): " << (t_nonzero ? "true" : "false") << " (ожидается true)" << endl;

    Time t6 = t1 + t2;
    cout << "7. t1 + t2 (10:30 + 2:45): " << t6 << " (ожидается 13:15)" << endl;

    Time t7 = t1 + 100;
    cout << "8. t1 + 100 минут: " << t7 << " (ожидается 12:10)" << endl;

    Time t8 = t2 - t1;
    cout << "9. t2 - t1 (2:45 - 10:30, переход в прошлые сутки): " << t8 << " (ожидается 16:15)" << endl;

    Time t9 = t1 - 70;
    cout << "10. t1 - 70 минут: " << t9 << " (ожидается 09:20)" << endl;

    return 0;
}