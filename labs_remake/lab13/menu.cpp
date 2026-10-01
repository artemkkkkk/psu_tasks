#include "menu.h"
#include "utils.h"
#include "stl3alg6.h"
#include "stl3alg16.h"
#include "stl3alg36.h"
#include "stl3alg60.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа №13. Обобщенные алгоритмы STL.\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - STL3Alg6\n";
    std::cout << "2 - STL3Alg16\n";
    std::cout << "3 - STL3Alg36\n";
    std::cout << "4 - STL3Alg60\n";
    std::cout << "5 - Выход\n";

    int choice = 0;
    if (!readInt("> ", 1, 5, choice)) {
        return 0;
    }

    return choice;
}

static int chooseInputMode() {
    std::cout << "\nВыберите способ ввода:\n";
    std::cout << "1 - вручную\n";
    std::cout << "2 - случайные данные\n";
    std::cout << "3 - из файла\n";

    int mode = 0;
    if (!readInt("> ", 1, 3, mode)) {
        return 0;
    }

    return mode;
}

void mainMenu() {
    while (true) {
        int task = chooseTask();
        if (task == 0 || task == 5) {
            break;
        }

        int mode = chooseInputMode();
        if (mode == 0) {
            break;
        }

        if (task == 1) {
            runSTL3Alg6(mode);
        } else if (task == 2) {
            runSTL3Alg16(mode);
        } else if (task == 3) {
            runSTL3Alg36(mode);
        } else if (task == 4) {
            runSTL3Alg60(mode);
        }
    }
}