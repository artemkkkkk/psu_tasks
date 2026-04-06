#include <iostream>
#include <string>
#include "backrec4.h"
#include "homedyn1.h"
#include "homedyn13.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void showMenu() {
    cout << "\n========================================" << endl;
    cout << "       ЛАБОРАТОРНАЯ РАБОТА №8           " << endl;
    cout << "========================================" << endl;
    cout << "Выберите задачу для решения:" << endl;
    cout << "1. BackRec4  (Археолог: вес [A,B], мин объем)" << endl;
    cout << "2. HomeDyn1  (Черепашка: макс сумма, Правый Верх -> Левый Низ)" << endl;
    cout << "3. HomeDyn13 (K-ичные числа без '00')" << endl;
    cout << "0. Выход" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Внимание: Для работы задач необходим файл 'input.txt' в папке программы." << endl;
    cout << "Результат будет записан в 'output.txt'." << endl;
    cout << "========================================" << endl;
    cout << "Ваш выбор: ";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cout << "Некорректный ввод. Попробуйте снова." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                solveBackRec4();
                break;
            case 2:
                solveHomeDyn1();
                break;
            case 3:
                solveHomeDyn13();
                break;
            case 0:
                cout << "Выход из программы." << endl;
                return 0;
            default:
                cout << "Неверный номер задачи. Выберите от 0 до 3." << endl;
        }

        cout << "\nНажмите Enter для продолжения...";
        cin.ignore();
        cin.get();
    }
}