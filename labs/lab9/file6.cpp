#include "file6.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void solveFile6() {
    cout << "\n--- Запуск задачи File6 ---" << endl;
    cout << "Введите имя двоичного файла: ";
    string filename;
    cin >> filename;

    cout << "Введите номер элемента K (нумерация с 1): ";
    int K;
    if (!(cin >> K) || K <= 0) {
        cerr << "Ошибка: Неверный номер элемента." << endl;
        return;
    }

    ifstream dataFile(filename, ios::binary);
    if (!dataFile.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл: " << filename << endl;
        ofstream fout("output.txt");
        if (fout) { fout << -1; fout.close(); }
        return;
    }

    int value;
    int count = 0;
    int result = -1;
    bool found = false;

    while (dataFile.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        count++;
        if (count == K) {
            result = value;
            found = true;
            break;
        }
    }
    dataFile.close();

    ofstream fout("output.txt");
    if (fout.is_open()) {
        fout << result << endl;
        fout.close();

        if (found) {
            cout << "Результат записан в output.txt: " << result << endl;
        } else {
            cout << "Элемент с номером " << K << " не найден (файл слишком короткий)." << endl;
            cout << "В output.txt записано: -1" << endl;
        }
    }
}