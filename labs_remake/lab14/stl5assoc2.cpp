#include "stl5assoc2.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

static void printIntVector(const std::vector<int>& V) {
    bool first = true;

    for (std::vector<int>::const_iterator it = V.begin(); it != V.end(); ++it) {
        if (!first) {
            std::cout << ' ';
        }

        std::cout << *it;
        first = false;
    }

    std::cout << '\n';
}

static bool inputManual(std::vector<int>& V0, std::vector<std::vector<int> >& others) {
    int size0 = 0;

    if (!readInt("Размер вектора V0: ", 1, 8, size0)) {
        return false;
    }

    V0.clear();

    for (int i = 0; i < size0; ++i) {
        std::cout << "Элемент V0 " << (i + 1) << ": ";

        int x = 0;
        if (!readIntNoPrompt(-100, 100, x)) {
            return false;
        }

        V0.push_back(x);
    }

    int N = 0;
    if (!readInt("Количество векторов V1...VN: ", 1, 5, N)) {
        return false;
    }

    others.clear();
    others.resize(N);

    for (int i = 0; i < N; ++i) {
        int sizeI = 0;

        std::cout << "Размер вектора V" << (i + 1) << ": ";

        if (!readIntNoPrompt(size0, 12, sizeI)) {
            return false;
        }

        others[i].clear();

        for (int j = 0; j < sizeI; ++j) {
            std::cout << "Элемент вектора V" << (i + 1) << " " << (j + 1) << ": ";

            int x = 0;
            if (!readIntNoPrompt(-100, 100, x)) {
                return false;
            }

            others[i].push_back(x);
        }
    }

    return true;
}

static bool inputRandom(std::vector<int>& V0, std::vector<std::vector<int> >& others) {
    initRandom();

    int size0 = randomInt(2, 4);
    int N = randomInt(3, 5);

    V0.clear();

    for (int i = 0; i < size0; ++i) {
        V0.push_back(randomInt(0, 9));
    }

    others.clear();
    others.resize(N);

    for (int i = 0; i < N; ++i) {
        int sizeI = size0 + randomInt(0, 3);
        others[i].clear();

        if (randomInt(0, 1) == 0) {
            for (int j = 0; j < size0; ++j) {
                others[i].push_back(V0[j]);
            }

            while (static_cast<int>(others[i].size()) < sizeI) {
                others[i].push_back(randomInt(0, 9));
            }
        } else {
            for (int j = 0; j < sizeI; ++j) {
                others[i].push_back(randomInt(0, 9));
            }
        }
    }

    std::cout << "\nСлучайные данные:\n";

    std::cout << "V0: ";
    printIntVector(V0);

    for (int i = 0; i < N; ++i) {
        std::cout << "V" << (i + 1) << ": ";
        printIntVector(others[i]);
    }

    return true;
}

static bool inputFile(std::vector<int>& V0, std::vector<std::vector<int> >& others) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    int size0 = 0;
    if (!(in >> size0)) {
        std::cout << "Не удалось прочитать размер вектора V0.\n";
        return false;
    }

    if (size0 < 1 || size0 > 100000) {
        std::cout << "Некорректный размер вектора V0.\n";
        return false;
    }

    V0.clear();

    for (int i = 0; i < size0; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы вектора V0.\n";
            return false;
        }

        V0.push_back(x);
    }

    int N = 0;
    if (!(in >> N)) {
        std::cout << "Не удалось прочитать количество векторов.\n";
        return false;
    }

    if (N < 1 || N > 10000) {
        std::cout << "Некорректное количество векторов.\n";
        return false;
    }

    others.clear();
    others.resize(N);

    for (int i = 0; i < N; ++i) {
        int sizeI = 0;

        if (!(in >> sizeI)) {
            std::cout << "Не удалось прочитать размер вектора V" << (i + 1) << ".\n";
            return false;
        }

        if (sizeI < size0 || sizeI > 100000) {
            std::cout << "Некорректный размер вектора V" << (i + 1) << ".\n";
            return false;
        }

        others[i].clear();

        for (int j = 0; j < sizeI; ++j) {
            int x = 0;

            if (!(in >> x)) {
                std::cout << "Не удалось прочитать элементы вектора V" << (i + 1) << ".\n";
                return false;
            }

            others[i].push_back(x);
        }
    }

    return true;
}

static int countIncludedVectors(
    const std::vector<int>& V0,
    const std::vector<std::vector<int> >& others
) {
    std::set<int> base(V0.begin(), V0.end());
    int result = 0;

    for (
        std::vector<std::vector<int> >::const_iterator it = others.begin();
        it != others.end();
        ++it
    ) {
        std::set<int> current(it->begin(), it->end());

        if (std::includes(current.begin(), current.end(), base.begin(), base.end())) {
            ++result;
        }
    }

    return result;
}

void runSTL5Assoc2(int mode) {
    std::vector<int> V0;
    std::vector<std::vector<int> > others;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(V0, others);
    } else if (mode == 2) {
        ok = inputRandom(V0, others);
    } else if (mode == 3) {
        ok = inputFile(V0, others);
    }

    if (!ok) {
        return;
    }

    if (V0.empty()) {
        std::cout << "Вектор V0 не может быть пустым.\n";
        return;
    }

    for (
        std::vector<std::vector<int> >::const_iterator it = others.begin();
        it != others.end();
        ++it
    ) {
        if (it->size() < V0.size()) {
            std::cout << "Размер каждого вектора V1...VN должен быть не меньше размера V0.\n";
            return;
        }
    }

    std::cout << "\nИсходный вектор V0: ";
    printIntVector(V0);

    std::cout << "Набор векторов:\n";

    for (int i = 0; i < static_cast<int>(others.size()); ++i) {
        std::cout << "V" << (i + 1) << ": ";
        printIntVector(others[i]);
    }

    int result = countIncludedVectors(V0, others);

    std::cout << "Количество векторов, содержащих все элементы V0 без учета повторений: "
              << result << '\n';
}