#include "menu.h"
#include "utils.h"
#include "dynamic3.h"
#include "dynamic24.h"
#include "listwork1.h"
#include "listwork22.h"
#include "listwork59.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа №10. Односвязные списки.\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - Dynamic3\n";
    std::cout << "2 - Dynamic24\n";
    std::cout << "3 - ListWork1\n";
    std::cout << "4 - ListWork22\n";
    std::cout << "5 - ListWork59\n";
    std::cout << "6 - Выход\n";

    int choice = 0;
    if (!readInt("> ", 1, 6, choice)) {
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
        if (task == 0 || task == 6) {
            break;
        }

        int mode = chooseInputMode();
        if (mode == 0) {
            break;
        }

        if (task == 1) {
            runDynamic3(mode);
        } else if (task == 2) {
            runDynamic24(mode);
        } else if (task == 3) {
            runListWork1(mode);
        } else if (task == 4) {
            runListWork22(mode);
        } else if (task == 5) {
            runListWork59(mode);
        }
    }
}