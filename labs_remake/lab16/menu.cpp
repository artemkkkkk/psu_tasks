#include "menu.h"
#include "utils.h"
#include "treework1.h"
#include "treework14.h"
#include "treework17.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа №16. Бинарные деревья.\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - TreeWork1\n";
    std::cout << "2 - TreeWork14\n";
    std::cout << "3 - TreeWork17\n";
    std::cout << "4 - Выход\n";

    int choice = 0;
    if (!readInt("> ", 1, 4, choice)) {
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
        if (task == 0 || task == 4) {
            break;
        }

        int mode = chooseInputMode();
        if (mode == 0) {
            break;
        }

        if (task == 1) {
            runTreeWork1(mode);
        } else if (task == 2) {
            runTreeWork14(mode);
        } else if (task == 3) {
            runTreeWork17(mode);
        }
    }
}