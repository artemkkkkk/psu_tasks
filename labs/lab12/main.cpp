#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <limits>
#include "stl2seq5.h"
#include "stl2seq8.h"
#include "stl2seq34.h"
#include "stl1iter8.h"

using namespace std;

void showMenu() {
    cout << "\n========================================" << endl;
    cout << "       ЛАБОРАТОРНАЯ РАБОТА №12          " << endl;
    cout << "       Вариант 1                        " << endl;
    cout << "========================================" << endl;
    cout << "1. STL2Seq5  (Список: вывод третей в разном порядке)" << endl;
    cout << "2. STL2Seq8  (Вектор: вставка 5 нулей в середину)" << endl;
    cout << "3. STL2Seq34 (Два списка: комбинирование через splice)" << endl;
    cout << "4. STL1Iter8 (Файл: копирование слов длиной <= K)" << endl;
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
                solveSTL2Seq5();
                break;
            case 2:
                solveSTL2Seq8();
                break;
            case 3:
                solveSTL2Seq34();
                break;
            case 4:
                solveSTL1Iter8();
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