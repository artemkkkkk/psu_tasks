#include "task1.h"
#include "time.h"
#include "timeinput.h"
#include <iostream>

void runTask1(int mode) {
    int hours = 0;
    int minutes = 0;
    unsigned addMinutes = 0;

    if (!inputTimeData(mode, hours, minutes, addMinutes)) {
        return;
    }

    Time def;
    Time t(static_cast<unsigned char>(hours), static_cast<unsigned char>(minutes));
    Time fromTotal(static_cast<unsigned>(hours) * 60u + static_cast<unsigned>(minutes));

    std::cout << "\nПроверка конструкторов:\n";
    std::cout << "Конструктор по умолчанию: " << def << '\n';
    std::cout << "Конструктор (часы, минуты): " << t << '\n';
    std::cout << "Конструктор (минуты с начала суток): " << fromTotal << '\n';

    Time result = t.addMinutes(addMinutes);

    std::cout << "\nДобавление " << addMinutes << " минут к " << t << ": "
              << result << '\n';
}