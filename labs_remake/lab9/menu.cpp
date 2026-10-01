#include "menu.h"
#include "utils.h"
#include "file6.h"
#include "file29.h"
#include "file48.h"
#include "recur14.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа №9. Двоичные файлы и рекурсия.\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - File6\n";
    std::cout << "2 - File29\n";
    std::cout << "3 - File48\n";
    std::cout << "4 - Recur14\n";
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
            runFile6(mode);
        } else if (task == 2) {
            runFile29(mode);
        } else if (task == 3) {
            runFile48(mode);
        } else if (task == 4) {
            runRecur14(mode);
        }
    }
}