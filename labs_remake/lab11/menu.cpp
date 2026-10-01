#include "menu.h"
#include "utils.h"
#include "listwork66.h"
#include "listwork42.h"
#include "listwork43.h"
#include "listwork46.h"
#include "texttask1.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа №11. Двусвязные и циклические списки.\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - ListWork66\n";
    std::cout << "2 - ListWork42\n";
    std::cout << "3 - ListWork43\n";
    std::cout << "4 - ListWork46\n";
    std::cout << "5 - Текстовая задача 1\n";
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
            runListWork66(mode);
        } else if (task == 2) {
            runListWork42(mode);
        } else if (task == 3) {
            runListWork43(mode);
        } else if (task == 4) {
            runListWork46(mode);
        } else if (task == 5) {
            runTextTask1(mode);
        }
    }
}