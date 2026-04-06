#include "stl2seq8.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void solveSTL2Seq8() {
    cout << "\n--- Задача STL2Seq8 ---" << endl;

    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Ошибка: Не удалось открыть input.txt" << endl;
        return;
    }

    vector<int> v;
    int x;
    while (fin >> x) {
        v.push_back(x);
    }
    fin.close();

    if (v.empty() || v.size() % 2 != 0) {
        cerr << "Ошибка: Количество элементов должно быть четным." << endl;
        return;
    }

    size_t mid = v.size() / 2;
    v.insert(v.begin() + mid, 5, 0);

    cout << "После вставки 5 нулей в середину:" << endl;
    for (int val : v) {
        cout << val << " ";
    }
    cout << endl;

    ofstream fout("output.txt");
    if (fout.is_open()) {
        for (size_t i = 0; i < v.size(); ++i) {
            fout << v[i];
            if (i != v.size() - 1) fout << " ";
        }
        fout << endl;
        fout.close();
        cout << "Результат записан в output.txt" << endl;
    }
}