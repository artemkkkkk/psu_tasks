#include "menu.h"
#include "utils.h"
#include "calctree1.h"
#include "calctree23.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа №17. Бинарные деревья (CalcTree).\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - CalcTree1\n";
    std::cout << "2 - CalcTree23\n";
    std::cout << "3 - Выход\n";

    int choice = 0;
    if (!readInt("> ", 1, 3, choice)) {
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
        if (task == 0 || task == 3) {
            break;
        }

        int mode = chooseInputMode();
        if (mode == 0) {
            break;
        }

        if (task == 1) {
            runCalcTree1(mode);
        } else if (task == 2) {
            runCalcTree23(mode);
        }
    }
}