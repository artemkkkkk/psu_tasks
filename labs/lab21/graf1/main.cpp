#include <iostream>
#include <fstream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Ошибка: не удалось открыть файл input.txt" << endl;
        return 1;
    }

    int n;
    if (!(fin >> n)) {
        cerr << "Ошибка чтения количества вершин." << endl;
        return 1;
    }

    vector<int> degree(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int val;
            fin >> val;
            if (val != 0) {
                if (i == j) {
                    degree[i] += 2;
                } else {
                    degree[i] += 1;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << degree[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    fin.close();
    return 0;
}