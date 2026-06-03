#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

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
    if (!(fin >> n)) return 1;

    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> adj[i][j];
        }
    }

    int k;
    if (!(fin >> k)) {
        cout << "Введите номер начальной вершины K: ";
        cin >> k;
    }
    k--;

    vector<bool> visited(n, false);
    queue<int> q;
    vector<int> result;

    q.push(k);
    visited[k] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u + 1);

        vector<int> neighbors;
        for (int v = 0; v < n; ++v) {
            if (adj[u][v] != 0 && !visited[v]) {
                neighbors.push_back(v);
            }
        }

        sort(neighbors.begin(), neighbors.end());

        for (int v : neighbors) {
            visited[v] = true;
            q.push(v);
        }
    }

    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    cout << endl;

    fin.close();
    return 0;
}