#include "menu.h"
#include "utils.h"
#include "treefun1.h"
#include "treefun3.h"
#include "treefun11.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа №18. Бинарные деревья и списки.\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - TreeFun1\n";
    std::cout << "2 - TreeFun3\n";
    std::cout << "3 - TreeFun11\n";
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
            runTreeFun1(mode);
        } else if (task == 2) {
            runTreeFun3(mode);
        } else if (task == 3) {
            runTreeFun11(mode);
        }
    }
}