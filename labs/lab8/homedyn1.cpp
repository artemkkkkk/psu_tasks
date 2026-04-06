#include "homedyn1.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void solveHomeDyn1() {
    cout << "\n--- Запуск задачи HomeDyn1 (Черепашка: Правый Верх -> Левый Низ, Макс Сумма) ---" << endl;

    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Ошибка: Не удалось открыть input.txt" << endl;
        return;
    }

    int N;
    if (!(fin >> N)) {
        cerr << "Ошибка чтения N" << endl;
        return;
    }

    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            fin >> board[i][j];
        }
    }
    fin.close();

    vector<vector<long long>> dp(N, vector<long long>(N, -1));

    dp[0][N-1] = board[0][N-1];

    for (int r = 0; r < N; ++r) {
        for (int c = N - 1; c >= 0; --c) {
            if (r == 0 && c == N - 1) continue;

            long long fromTop = -1;
            long long fromRight = -1;

            if (r > 0 && dp[r-1][c] != -1) {
                fromTop = dp[r-1][c];
            }

            if (c < N - 1 && dp[r][c+1] != -1) {
                fromRight = dp[r][c+1];
            }

            if (fromTop != -1 || fromRight != -1) {
                dp[r][c] = board[r][c] + max(fromTop, fromRight);
            }
        }
    }

    long long result = dp[N-1][0];

    ofstream fout("output.txt");
    if (fout.is_open()) {
        fout << result << endl;
        fout.close();
        cout << "Результат записан в output.txt" << endl;
        cout << "Максимальная сумма: " << result << endl;
    } else {
        cerr << "Ошибка записи в output.txt" << endl;
    }
}