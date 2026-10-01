#include "menu.h"
#include "utils.h"
#include "backrec4.h"
#include "homedyn1.h"
#include "homedyn13.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа 8.\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - BackRec4\n";
    std::cout << "2 - HomeDyn1\n";
    std::cout << "3 - HomeDyn13\n";
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
            runBackRec4(mode);
        } else if (task == 2) {
            runHomeDyn1(mode);
        } else if (task == 3) {
            runHomeDyn13(mode);
        }
    }
}