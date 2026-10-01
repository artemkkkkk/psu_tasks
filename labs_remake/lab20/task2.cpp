#include "task2.h"
#include "time.h"
#include "timeinput.h"
#include <iostream>

void runTask2(int mode) {
    int hours = 0;
    int minutes = 0;
    unsigned addMinutes = 0;

    if (!inputTimeData(mode, hours, minutes, addMinutes)) {
        return;
    }

    Time t(static_cast<unsigned char>(hours), static_cast<unsigned char>(minutes));

    std::cout << "\nИсходное время: " << t << '\n';

    ++t;
    std::cout << "После ++t: " << t << '\n';

    Time postInc = t++;
    std::cout << "t++ вернул " << postInc << ", время стало " << t << '\n';

    --t;
    std::cout << "После --t: " << t << '\n';

    Time postDec = t--;
    std::cout << "t-- вернул " << postDec << ", время стало " << t << '\n';

    std::cout << "Приведение к short int (часы): " << static_cast<short>(t) << '\n';

    if (t) {
        std::cout << "Приведение к bool: true (время не нулевое)\n";
    } else {
        std::cout << "Приведение к bool: false (нулевое время)\n";
    }

    Time zero;

    if (zero) {
        std::cout << "Нулевое время дало true\n";
    } else {
        std::cout << "Нулевое время дало false\n";
    }

    std::cout << t << " + " << addMinutes << " минут = " << (t + addMinutes) << '\n';
    std::cout << t << " - " << addMinutes << " минут = " << (t - addMinutes) << '\n';
}