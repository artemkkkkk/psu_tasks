#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <limits>
#include "file6.h"
#include "file29.h"
#include "file48.h"
#include "recur14.h"

using namespace std;

void showMenu() {
    cout << "\n========================================" << endl;
    cout << "       ЛАБОРАТОРНАЯ РАБОТА №9           " << endl;
    cout << "========================================" << endl;
    cout << "Выберите задачу для решения:" << endl;
    cout << "1. File6   (K-й элемент двоичного файла)" << endl;
    cout << "2. File29  (Усечь файл до 50 элементов)" << endl;
    cout << "3. File48  (Слияние 3 файлов в один)" << endl;
    cout << "4. Recur14 (Вычисление выражения рекурсивно)" << endl;
    cout << "0. Выход" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Внимание: Для работы задач необходим файл 'input.txt'." << endl;
    cout << "Результат будет записан в 'output.txt' или изменены указанные файлы." << endl;
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Попробуйте снова." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                solveFile6();
                break;
            case 2:
                solveFile29();
                break;
            case 3:
                solveFile48();
                break;
            case 4:
                solveRecur14();
                break;
            case 0:
                cout << "Выход из программы." << endl;
                return 0;
            default:
                cout << "Неверный номер задачи. Выберите от 0 до 4." << endl;
        }

        cout << "\nНажмите Enter для продолжения...";
        cin.ignore();
        cin.get();
    }
}