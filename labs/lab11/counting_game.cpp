#include "counting_game.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

using namespace std;

void solveCountingGame1() {
    cout << "\n--- Текстовая задача 1 (Считалка) ---" << endl;
    
    ifstream fin("input_game.txt");
    if (!fin.is_open()) {
        cerr << "Ошибка: Не удалось открыть input_game.txt" << endl;
        cout << "Создайте файл input_game.txt. Первая строка - K (шаг), далее имена." << endl;
        return;
    }

    int K;
    if (!(fin >> K)) {
        cerr << "Ошибка чтения K" << endl;
        return;
    }

    list<string> children;
    string name;
    while (fin >> name) {
        children.push_back(name);
    }
    fin.close();

    if (children.empty()) {
        cout << "Нет детей." << endl;
        return;
    }

    ofstream fout("output_game.txt");
    if (!fout.is_open()) {
        cerr << "Ошибка записи в output_game.txt" << endl;
        return;
    }

    auto it = children.begin();
    while (!children.empty()) {
        for (int i = 0; i < K - 1; ++i) {
            ++it;
            if (it == children.end()) {
                it = children.begin();
            }
        }
        
        fout << *it << endl;
        it = children.erase(it);
        if (it == children.end()) {
            it = children.begin();
        }
    }
    
    fout.close();
    cout << "Результат записан в output_game.txt" << endl;
}