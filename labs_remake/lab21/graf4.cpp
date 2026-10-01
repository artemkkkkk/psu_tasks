#include "graf4.h"
#include "graph.h"
#include "utils.h"
#include <iostream>

void runGraf4(int mode) {
    Graph g;
    int k = 0;

    bool ok = false;

    if (mode == 1) {
        ok = readGraphManual(g, false, 100);

        if (ok) {
            if (!readInt("Номер стартовой вершины: ", 1, g.n, k)) {
                return;
            }
        }
    } else if (mode == 2) {
        ok = readGraphRandom(g, false, 100);

        if (ok) {
            initRandom();
            k = randomInt(1, g.n);
            std::cout << "Стартовая вершина: " << k << '\n';
        }
    } else if (mode == 3) {
        char fileName[256];

        if (!readFileName("Введите имя файла: ", fileName, 256)) {
            return;
        }

        int extra[1];
        ok = readGraphFile(g, fileName, extra, 1);

        if (ok) {
            k = extra[0];

            if (k < 1 || k > g.n) {
                std::cout << "Некорректный номер стартовой вершины.\n";
                return;
            }
        }
    }

    if (!ok) {
        return;
    }

    std::cout << "\nМатрица смежности:\n";
    printGraph(g);

    bool visited[MAX_N];
    int queue[MAX_N];
    int order[MAX_N];

    for (int i = 0; i < g.n; ++i) {
        visited[i] = false;
    }

    int front = 0;
    int back = 0;
    int count = 0;

    visited[k - 1] = true;
    queue[back++] = k - 1;

    while (front < back) {
        int v = queue[front++];
        order[count++] = v + 1;

        for (int to = 0; to < g.n; ++to) {
            if (g.m[v][to] != 0 && !visited[to]) {
                visited[to] = true;
                queue[back++] = to;
            }
        }
    }

    std::cout << "\nПорядок обхода в ширину из вершины " << k << ":\n";

    for (int i = 0; i < count; ++i) {
        std::cout << order[i] << ' ';
    }

    std::cout << '\n';
}