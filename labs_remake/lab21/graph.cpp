#include "graph.h"
#include "utils.h"
#include <iostream>
#include <fstream>

bool readGraphManual(Graph& g, bool symmetric, int maxValue) {
    if (!readInt("Количество вершин: ", 1, 10, g.n)) {
        return false;
    }

    std::cout << "Вводите элементы матрицы смежности (0.. " << maxValue << "):\n";

    for (int i = 0; i < g.n; ++i) {
        for (int j = 0; j < g.n; ++j) {
            if (symmetric && j < i) {
                g.m[i][j] = g.m[j][i];
                continue;
            }

            std::cout << "m[" << (i + 1) << "][" << (j + 1) << "]: ";

            int v = 0;
            if (!readIntNoPrompt(0, maxValue, v)) {
                return false;
            }

            g.m[i][j] = v;

            if (symmetric) {
                g.m[j][i] = v;
            }
        }
    }

    return true;
}

bool readGraphRandom(Graph& g, bool symmetric, int maxValue) {
    initRandom();

    g.n = randomInt(4, 8);

    for (int i = 0; i < g.n; ++i) {
        for (int j = 0; j < g.n; ++j) {
            if (symmetric && j < i) {
                g.m[i][j] = g.m[j][i];
                continue;
            }

            int v = 0;

            if (randomInt(0, 99) < 35) {
                v = randomInt(1, maxValue);
            }

            g.m[i][j] = v;

            if (symmetric) {
                g.m[j][i] = v;
            }
        }
    }

    std::cout << "\nСлучайный граф построен. Количество вершин: " << g.n << '\n';
    return true;
}

bool readGraphFile(Graph& g, const char* fileName, int* extra, int extraCount) {
    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    if (!(in >> g.n)) {
        std::cout << "Не удалось прочитать количество вершин.\n";
        return false;
    }

    if (g.n < 1 || g.n > MAX_N) {
        std::cout << "Некорректное количество вершин.\n";
        return false;
    }

    for (int i = 0; i < g.n; ++i) {
        for (int j = 0; j < g.n; ++j) {
            if (!(in >> g.m[i][j])) {
                std::cout << "Не удалось прочитать матрицу смежности.\n";
                return false;
            }
        }
    }

    for (int i = 0; i < extraCount; ++i) {
        if (!(in >> extra[i])) {
            std::cout << "Не удалось прочитать дополнительные параметры.\n";
            return false;
        }
    }

    return true;
}

void printGraph(const Graph& g) {
    for (int i = 0; i < g.n; ++i) {
        for (int j = 0; j < g.n; ++j) {
            std::cout << g.m[i][j] << ' ';
        }

        std::cout << '\n';
    }
}