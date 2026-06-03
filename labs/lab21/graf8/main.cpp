#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const int INF = 1e9;

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
    if (!(fin >> n)) return 1;

    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> adj[i][j];
        }
    }

    int k, l;
    if (!(fin >> k >> l)) {
        cout << "Введите номер города K и количество пересадок L через пробел: ";
        cin >> k >> l;
    }
    k--;

    vector<int> dist(n, INF);
    queue<int> q;

    dist[k] = 0;
    q.push(k);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            if (adj[u][v] != 0 && dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    vector<int> result;
    for (int i = 0; i < n; ++i) {
        if (i != k && dist[i] != INF && dist[i] >= l + 1) {
            result.push_back(i + 1);
        }
    }

    sort(result.begin(), result.end());

    if (result.empty()) {
        cout << -1 << endl;
    } else {
        for (size_t i = 0; i < result.size(); ++i) {
            cout << result[i] << (i == result.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    fin.close();
    return 0;
}