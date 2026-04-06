#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <limits>
#include "stack.h"
#include "queue.h"
#include "list.h"

using namespace std;

void showMenu() {
    cout << "\n========================================" << endl;
    cout << "       ЛАБОРАТОРНАЯ РАБОТА №10          " << endl;
    cout << "       Вариант 1                        " << endl;
    cout << "========================================" << endl;
    cout << "1. Dynamic3  (Стек: добавить элемент, вывести адрес вершины)" << endl;
    cout << "2. Dynamic24 (Очередь: объединить две очереди чередованием)" << endl;
    cout << "3. ListWork1 (Список: указатель на 2-й элемент)" << endl;
    cout << "4. ListWork22 (Список: вставить M после каждого 2-го)" << endl;
    cout << "5. ListWork59 (Список: вставить M после каждого K-го)" << endl;
    cout << "0. Выход" << endl;
    cout << "========================================" << endl;
    cout << "Ваш выбор: ";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                runDynamic3();
                break;
            case 2:
                runDynamic24();
                break;
            case 3:
                runListWork1();
                break;
            case 4:
                runListWork22();
                break;
            case 5:
                runListWork59();
                break;
            case 0:
                cout << "Выход." << endl;
                return 0;
            default:
                cout << "Неверный номер." << endl;
        }

        cout << "\nНажмите Enter для продолжения...";
        cin.ignore();
        cin.get();
    }
}