#include "homedyn13.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

void solveHomeDyn13() {
    cout << "\n--- Запуск задачи HomeDyn13 (K-ичные числа, нет '00') ---" << endl;

    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Ошибка: Не удалось открыть input.txt" << endl;
        return;
    }

    int K, N;
    if (!(fin >> K >> N)) {
        cerr << "Ошибка чтения K и N" << endl;
        return;
    }
    fin.close();

    vector<vector<double>> dp(N + 1, vector<double>(2, 0));

    dp[1][0] = 0;
    dp[1][1] = K - 1;

    for (int i = 2; i <= N; ++i) {
        dp[i][0] = dp[i-1][1];

        dp[i][1] = (dp[i-1][0] + dp[i-1][1]) * (K - 1);
    }

    double total = dp[N][0] + dp[N][1];

    ofstream fout("output.txt");
    if (fout.is_open()) {
        fout << fixed << setprecision(0);
        fout << total << endl;
        fout.close();
        cout << "Результат записан в output.txt" << endl;
        cout << "Количество чисел: " << total << endl;
    } else {
        cerr << "Ошибка записи в output.txt" << endl;
    }
}