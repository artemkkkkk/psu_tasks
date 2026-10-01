#include "graf8.h"
#include "graph.h"
#include "utils.h"
#include <iostream>

void runGraf8(int mode) {
    Graph g;
    int K = 0;
    int L = 0;

    bool ok = false;

    if (mode == 1) {
        ok = readGraphManual(g, false, 1);

        if (ok) {
            if (!readInt("Номер города K: ", 1, g.n, K)) {
                return;
            }

            if (!readInt("Количество пересадок L: ", 0, 100, L)) {
                return;
            }
        }
    } else if (mode == 2) {
        ok = readGraphRandom(g, false, 1);

        if (ok) {
            initRandom();
            K = randomInt(1, g.n);
            L = randomInt(1, 3);
            std::cout << "K = " << K << ", L = " << L << '\n';
        }
    } else if (mode == 3) {
        char fileName[256];

        if (!readFileName("Введите имя файла: ", fileName, 256)) {
            return;
        }

        int extra[2];
        ok = readGraphFile(g, fileName, extra, 2);

        if (ok) {
            K = extra[0];
            L = extra[1];

            if (K < 1 || K > g.n || L < 0) {
                std::cout << "Некорректные параметры K и L.\n";
                return;
            }
        }
    }

    if (!ok) {
        return;
    }

    std::cout << "\nМатрица смежности:\n";
    printGraph(g);

    int dist[MAX_N];
    int queue[MAX_N];

    for (int i = 0; i < g.n; ++i) {
        dist[i] = -1;
    }

    int front = 0;
    int back = 0;

    dist[K - 1] = 0;
    queue[back++] = K - 1;

    while (front < back) {
        int v = queue[front++];

        for (int to = 0; to < g.n; ++to) {
            if (g.m[v][to] != 0 && dist[to] == -1) {
                dist[to] = dist[v] + 1;
                queue[back++] = to;
            }
        }
    }

    std::cout << "\nГорода, достижимые не менее чем с " << L
              << " пересадками (без более коротких путей):\n";

    bool found = false;

    for (int v = 0; v < g.n; ++v) {
        if (v == K - 1) {
            continue;
        }

        if (dist[v] >= L + 1) {
            std::cout << (v + 1) << ' ';
            found = true;
        }
    }

    if (!found) {
        std::cout << -1;
    }

    std::cout << '\n';
}