#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <limits>
#include "dlist.h"
#include "clist.h"
#include "counting_game.h"

using namespace std;

void showMenu() {
    cout << "\n========================================" << endl;
    cout << "       ЛАБОРАТОРНАЯ РАБОТА №11          " << endl;
    cout << "========================================" << endl;
    cout << "1. ListWork66 (Цикл. односвязный: вывод с шагом 3)" << endl;
    cout << "2. ListWork42 (Цикл. двусвязный: удаление при равных соседях)" << endl;
    cout << "3. ListWork43 (Лин. двусвязный: нечетные в конец)" << endl;
    cout << "4. ListWork46 (Лин. двусвязный: барьерный элемент)" << endl;
    cout << "5. Counting Game 1 (Считалка из файла)" << endl;
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
                runListWork66();
                break;
            case 2:
                runListWork42();
                break;
            case 3:
                runListWork43();
                break;
            case 4:
                runListWork46();
                break;
            case 5:
                solveCountingGame1();
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