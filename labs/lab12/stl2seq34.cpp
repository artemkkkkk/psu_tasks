#include "stl2seq34.h"
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

void solveSTL2Seq34() {
    cout << "\n--- Задача STL2Seq34 ---" << endl;

    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Ошибка: Не удалось открыть input.txt" << endl;
        return;
    }

    list<int> l1, l2;
    int x;
    
    vector<int> allNumbers;
    while (fin >> x) {
        allNumbers.push_back(x);
    }
    fin.close();

    if (allNumbers.empty() || allNumbers.size() % 2 != 0) {
        cerr << "Ошибка: Нужно четное количество чисел (для двух равных списков)." << endl;
        return;
    }

    size_t half = allNumbers.size() / 2;
    l1.assign(allNumbers.begin(), allNumbers.begin() + half);
    l2.assign(allNumbers.begin() + half, allNumbers.end());

    if (l1.size() != l2.size()) {
        cerr << "Ошибка: Списки должны быть одинакового размера." << endl;
        return;
    }

    auto i1 = l1.begin();
    auto i2 = l2.begin();

    while (i1 != l1.end()) {
        l2.splice(i2, l1, i1++);
        ++i2;
        ++i2;
    }

    cout << "Комбинированный список L2:" << endl;
    for (int val : l2) {
        cout << val << " ";
    }
    cout << endl;

    ofstream fout("output.txt");
    if (fout.is_open()) {
        for (auto it = l2.begin(); it != l2.end(); ++it) {
            fout << *it;
            if (next(it) != l2.end()) fout << " ";
        }
        fout << endl;
        fout.close();
        cout << "Результат записан в output.txt" << endl;
    }
}