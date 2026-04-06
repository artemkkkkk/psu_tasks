#include "file48.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void solveFile48() {
    cout << "\n--- Запуск задачи File48 ---" << endl;

    string sa, sb, sc, sd;
    cout << "Введите имя первого файла (SA): ";
    cin >> sa;
    cout << "Введите имя второго файла (SB): ";
    cin >> sb;
    cout << "Введите имя третьего файла (SC): ";
    cin >> sc;
    cout << "Введите имя результирующего файла (SD): ";
    cin >> sd;

    ifstream fa(sa, ios::binary);
    ifstream fb(sb, ios::binary);
    ifstream fc(sc, ios::binary);

    if (!fa.is_open()) { cerr << "Ошибка открытия: " << sa << endl; return; }
    if (!fb.is_open()) { cerr << "Ошибка открытия: " << sb << endl; return; }
    if (!fc.is_open()) { cerr << "Ошибка открытия: " << sc << endl; return; }

    ofstream fout(sd, ios::binary);
    if (!fout.is_open()) {
        cerr << "Ошибка создания результирующего файла: " << sd << endl;
        return;
    }

    int a, b, c;
    bool eofReached = false;

    while (!eofReached) {
        bool ra = fa.read(reinterpret_cast<char*>(&a), sizeof(int)).good();
        bool rb = fb.read(reinterpret_cast<char*>(&b), sizeof(int)).good();
        bool rc = fc.read(reinterpret_cast<char*>(&c), sizeof(int)).good();

        if (!ra || !rb || !rc) {
            eofReached = true;
        } else {
            fout.write(reinterpret_cast<const char*>(&a), sizeof(int));
            fout.write(reinterpret_cast<const char*>(&b), sizeof(int));
            fout.write(reinterpret_cast<const char*>(&c), sizeof(int));
        }
    }

    fa.close();
    fb.close();
    fc.close();
    fout.close();

    cout << "Файл " << sd << " успешно создан путем чередования элементов." << endl;
    
    ofstream logOut("output.txt");
    if(logOut) {
        logOut << "Files merged successfully into " << sd << endl;
        logOut.close();
    }
}