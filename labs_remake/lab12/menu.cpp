#include "menu.h"
#include "utils.h"
#include "stl2seq5.h"
#include "stl2seq8.h"
#include "stl2seq34.h"
#include "stl1iter8.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа №12. STL.\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - STL2Seq5\n";
    std::cout << "2 - STL2Seq8\n";
    std::cout << "3 - STL2Seq34\n";
    std::cout << "4 - STL1Iter8\n";
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
            runSTL2Seq5(mode);
        } else if (task == 2) {
            runSTL2Seq8(mode);
        } else if (task == 3) {
            runSTL2Seq34(mode);
        } else if (task == 4) {
            runSTL1Iter8(mode);
        }
    }
}