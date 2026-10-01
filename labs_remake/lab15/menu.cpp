#include "menu.h"
#include "utils.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include <iostream>

static int chooseTask() {
    std::cout << "\nЛабораторная работа №15. Объектно-ориентированное программирование.\n";
    std::cout << "Выберите задачу:\n";
    std::cout << "1 - Задача 1: Точка координат\n";
    std::cout << "2 - Задача 2: Прямая\n";
    std::cout << "3 - Задача 3: Студент\n";
    std::cout << "4 - Задача 4: Создание Точки и Линии\n";
    std::cout << "5 - Задача 5: Длина Линии\n";
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
            runTask1(mode);
        } else if (task == 2) {
            runTask2(mode);
        } else if (task == 3) {
            runTask3(mode);
        } else if (task == 4) {
            runTask4(mode);
        } else if (task == 5) {
            runTask5(mode);
        }
    }
}