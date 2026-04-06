#include "stl2seq5.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

list<int> fillListFromVector(const vector<int>& v) {
    return list<int>(v.begin(), v.end());
}

list<int> fillListPushBack(const vector<int>& v) {
    list<int> lst;
    for (int x : v) {
        lst.push_back(x);
    }
    return lst;
}

list<int> fillListCopy(const vector<int>& v) {
    list<int> lst;
    copy(v.begin(), v.end(), back_inserter(lst));
    return lst;
}

void printListThirds(const list<int>& lst) {
    int n = lst.size();
    if (n % 3 != 0) {
        cout << "Ошибка: количество элементов не делится на 3." << endl;
        return;
    }

    int third = n / 3;

    auto it = lst.begin();
    advance(it, third);
    cout << "Первая треть (прямой): ";
    copy(lst.begin(), it, ostream_iterator<int>(cout, " "));
    cout << endl;

    auto mid_start = it;
    advance(it, third);
    cout << "Вторая треть (обратный): ";
    copy(make_reverse_iterator(it), make_reverse_iterator(mid_start), ostream_iterator<int>(cout, " "));
    cout << endl;

    auto last_start = it;
    cout << "Третья треть (обратный): ";
    copy(lst.rbegin(), make_reverse_iterator(last_start), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void solveSTL2Seq5() {
    cout << "\n--- Задача STL2Seq5 ---" << endl;

    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Ошибка: Не удалось открыть input.txt" << endl;
        return;
    }

    vector<int> numbers;
    int x;
    while (fin >> x) {
        numbers.push_back(x);
    }
    fin.close();

    if (numbers.empty() || numbers.size() % 3 != 0) {
        cerr << "Ошибка: Количество элементов должно быть кратно 3." << endl;
        return;
    }

    list<int> lst1 = fillListFromVector(numbers);
    list<int> lst2 = fillListPushBack(numbers);
    list<int> lst3 = fillListCopy(numbers);

    cout << "Список заполнен тремя способами." << endl;
    cout << "Результат для первого способа:" << endl;
    printListThirds(lst1);

    ofstream fout("output.txt");
    if (fout.is_open()) {
        int third = numbers.size() / 3;
        
        for (int i = 0; i < third; ++i) {
            fout << numbers[i] << " ";
        }
        fout << endl;

        for (int i = 2*third - 1; i >= third; --i) {
            fout << numbers[i] << " ";
        }
        fout << endl;

        for (int i = numbers.size() - 1; i >= 2*third; --i) {
            fout << numbers[i] << " ";
        }
        fout << endl;

        fout.close();
        cout << "Результат записан в output.txt" << endl;
    }
}