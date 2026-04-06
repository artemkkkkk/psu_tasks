#include "backrec4.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <functional>

using namespace std;

void solveBackRec4() {
    cout << "\n--- Запуск задачи BackRec4 (Археолог: вес [A,B], мин объем) ---" << endl;

    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Ошибка: Не удалось открыть input.txt" << endl;
        return;
    }

    int N;
    double A, B;
    if (!(fin >> N >> A >> B)) {
        cerr << "Ошибка чтения данных (N, A, B)" << endl;
        return;
    }

    vector<double> weights(N);
    vector<double> volumes(N);

    for (int i = 0; i < N; ++i) fin >> weights[i];
    for (int i = 0; i < N; ++i) fin >> volumes[i];
    fin.close();

    double minVol = 1e18;
    double bestWeight = 0;
    vector<int> bestSet;
    vector<int> currentSet;
    bool found = false;

    function<void(int, double, double)> backtrack = [&](int idx, double curW, double curV) {
        if (curV >= minVol) return;

        if (idx == N) {
            if (curW >= A && curW <= B) {
                if (!found || curV < minVol) {
                    minVol = curV;
                    bestWeight = curW;
                    bestSet = currentSet;
                    found = true;
                }
            }
            return;
        }

        backtrack(idx + 1, curW, curV);

        if (curW + weights[idx] <= B) {
            currentSet.push_back(idx + 1);
            backtrack(idx + 1, curW + weights[idx], curV + volumes[idx]);
            currentSet.pop_back();
        }
    };

    backtrack(0, 0.0, 0.0);

    ofstream fout("output.txt");
    if (fout.is_open()) {
        if (found) {
            sort(bestSet.begin(), bestSet.end());
            fout << "Индексы: ";
            for (int idx : bestSet) fout << idx << " ";
            fout << endl;
            fout << fixed << setprecision(2);
            fout << "Вес: " << bestWeight << endl;
            fout << "Объем: " << minVol << endl;

            cout << "Результат записан в output.txt" << endl;
            cout << "Индексы: ";
            for (int idx : bestSet) cout << idx << " ";
            cout << endl;
            cout << "Вес: " << bestWeight << ", Объем: " << minVol << endl;
        } else {
            fout << "Решение не найдено" << endl;
            cout << "Решение не найдено" << endl;
        }
        fout.close();
    }
}