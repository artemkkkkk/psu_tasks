#include "file29.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void solveFile29() {
    cout << "\n--- Запуск задачи File29 ---" << endl;
    cout << "Введите имя двоичного файла целых чисел: ";
    string filename;
    cin >> filename;

    ifstream inFile(filename, ios::binary | ios::in);
    if (!inFile.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл: " << filename << endl;
        return;
    }

    vector<int> numbers;
    int val;
    while (inFile.read(reinterpret_cast<char*>(&val), sizeof(int))) {
        numbers.push_back(val);
    }
    inFile.close();

    cout << "В файле найдено элементов: " << numbers.size() << endl;

    if (numbers.size() <= 50) {
        cout << "Файл уже содержит 50 или меньше элементов. Изменений не внесено." << endl;
        ofstream fout("output.txt");
        if(fout) { fout << "No changes made"; fout.close(); }
        return;
    }

    numbers.resize(50);

    ofstream outFile(filename, ios::binary | ios::out | ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Ошибка записи в файл: " << filename << endl;
        return;
    }

    for (int num : numbers) {
        outFile.write(reinterpret_cast<const char*>(&num), sizeof(int));
    }
    outFile.close();

    cout << "Размер файла " << filename << " успешно уменьшен до 50 элементов." << endl;

    ofstream fout("output.txt");
    if(fout) {
        fout << "File resized to 50 elements." << endl;
        fout.close();
    }
}