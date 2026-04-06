#include "stl1iter8.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

void solveSTL1Iter8() {
    cout << "\n--- Задача STL1Iter8 ---" << endl;

    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Ошибка: Не удалось открыть input.txt" << endl;
        return;
    }

    int K;
    string name1, name2;
    
    if (!(fin >> K >> name1 >> name2)) {
        cerr << "Ошибка чтения данных из input.txt" << endl;
        return;
    }
    fin.close();

    ifstream inFile(name1);
    ofstream outFile(name2);

    if (!inFile.is_open()) {
        cerr << "Ошибка открытия исходного файла: " << name1 << endl;
        return;
    }
    if (!outFile.is_open()) {
        cerr << "Ошибка создания результирующего файла: " << name2 << endl;
        return;
    }

    auto tooLong = [K](const string& s) {
        return s.length() > static_cast<size_t>(K);
    };

    remove_copy_if(
        istream_iterator<string>(inFile),
        istream_iterator<string>(),
        ostream_iterator<string>(outFile, "\n"),
        tooLong
    );

    inFile.close();
    outFile.close();

    cout << "Слова длиной <= " << K << " записаны в файл " << name2 << endl;
    
    ofstream logOut("output.txt");
    if (logOut.is_open()) {
        logOut << "Result written to " << name2 << endl;
        logOut.close();
    }
}