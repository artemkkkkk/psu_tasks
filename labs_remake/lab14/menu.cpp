#include "menu.h"
#include "utils.h"
#include "stl5assoc2.h"
#include "stl5assoc17.h"
#include "stl5assoc21.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа №14. Ассоциативные контейнеры STL.\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - STL5Assoc2\n";
    std::cout << "2 - STL5Assoc17\n";
    std::cout << "3 - STL5Assoc21\n";
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
            runSTL5Assoc2(mode);
        } else if (task == 2) {
            runSTL5Assoc17(mode);
        } else if (task == 3) {
            runSTL5Assoc21(mode);
        }
    }
}