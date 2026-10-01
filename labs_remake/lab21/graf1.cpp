#include "graf1.h"
#include "graph.h"
#include "utils.h"
#include <iostream>

void runGraf1(int mode) {
    Graph g;

    bool ok = false;

    if (mode == 1) {
        ok = readGraphManual(g, true, 1);
    } else if (mode == 2) {
        ok = readGraphRandom(g, true, 1);
    } else if (mode == 3) {
        char fileName[256];

        if (!readFileName("Введите имя файла: ", fileName, 256)) {
            return;
        }

        ok = readGraphFile(g, fileName, 0, 0);
    }

    if (!ok) {
        return;
    }

    std::cout << "\nМатрица смежности:\n";
    printGraph(g);

    std::cout << "\nСтепени вершин:\n";

    for (int i = 0; i < g.n; ++i) {
        int degree = 0;

        for (int j = 0; j < g.n; ++j) {
            if (g.m[i][j] != 0) {
                degree += (i == j) ? 2 : 1;
            }
        }

        std::cout << "Вершина " << (i + 1) << ": " << degree << '\n';
    }
}