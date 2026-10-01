#include "stl3alg16.h"
#include "utils.h"
#include "stlprint.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

static bool inputManual(std::vector<int>& V1, std::vector<int>& V2, int& A, int& B) {
    if (!readInt("Значение A: ", -1000, 1000, A)) {
        return false;
    }

    if (!readInt("Значение B: ", -1000, 1000, B)) {
        return false;
    }

    int countV1 = 0;
    if (!readInt("Размер первого вектора (не менее 10): ", 10, 20, countV1)) {
        return false;
    }

    int countV2 = 0;
    if (!readInt("Размер второго вектора (не менее 10): ", 10, 20, countV2)) {
        return false;
    }

    V1.clear();
    V2.clear();

    std::cout << "Элементы первого вектора:\n";

    for (int i = 0; i < countV1; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";

        int x = 0;
        if (!readIntNoPrompt(-1000, 1000, x)) {
            return false;
        }

        V1.push_back(x);
    }

    std::cout << "Элементы второго вектора:\n";

    for (int i = 0; i < countV2; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";

        int x = 0;
        if (!readIntNoPrompt(-1000, 1000, x)) {
            return false;
        }

        V2.push_back(x);
    }

    return true;
}

static bool inputRandom(std::vector<int>& V1, std::vector<int>& V2, int& A, int& B) {
    initRandom();

    A = randomInt(-10, 10);
    B = randomInt(-10, 10);

    int countV1 = randomInt(10, 14);
    int countV2 = randomInt(10, 14);

    V1.clear();
    V2.clear();

    for (int i = 0; i < countV1; ++i) {
        V1.push_back(randomInt(0, 99));
    }

    for (int i = 0; i < countV2; ++i) {
        V2.push_back(randomInt(0, 99));
    }

    std::cout << "\nСлучайные данные:\n";
    std::cout << "A = " << A << ", B = " << B << '\n';

    std::cout << "Первый вектор: ";
    bool first = true;
    printRange(V1.begin(), V1.end(), first);
    std::cout << '\n';

    std::cout << "Второй вектор: ";
    first = true;
    printRange(V2.begin(), V2.end(), first);
    std::cout << '\n';

    return true;
}

static bool inputFile(std::vector<int>& V1, std::vector<int>& V2, int& A, int& B) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    if (!(in >> A >> B)) {
        std::cout << "Не удалось прочитать значения A и B.\n";
        return false;
    }

    int countV1 = 0;
    if (!(in >> countV1)) {
        std::cout << "Не удалось прочитать размер первого вектора.\n";
        return false;
    }

    if (countV1 < 10 || countV1 > 100000) {
        std::cout << "Некорректный размер первого вектора.\n";
        return false;
    }

    V1.clear();

    for (int i = 0; i < countV1; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы первого вектора.\n";
            return false;
        }

        V1.push_back(x);
    }

    int countV2 = 0;
    if (!(in >> countV2)) {
        std::cout << "Не удалось прочитать размер второго вектора.\n";
        return false;
    }

    if (countV2 < 10 || countV2 > 100000) {
        std::cout << "Некорректный размер второго вектора.\n";
        return false;
    }

    V2.clear();

    for (int i = 0; i < countV2; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы второго вектора.\n";
            return false;
        }

        V2.push_back(x);
    }

    return true;
}

static void transformVectors(std::vector<int>& V1, std::vector<int>& V2, int A, int B) {
    std::fill(V1.begin(), V1.begin() + 5, A);
    std::fill(V1.end() - 5, V1.end(), B);

    std::fill_n(V2.begin(), 5, A);
    std::fill_n(V2.end() - 5, 5, B);
}

void runSTL3Alg16(int mode) {
    std::vector<int> V1;
    std::vector<int> V2;
    int A = 0;
    int B = 0;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(V1, V2, A, B);
    } else if (mode == 2) {
        ok = inputRandom(V1, V2, A, B);
    } else if (mode == 3) {
        ok = inputFile(V1, V2, A, B);
    }

    if (!ok) {
        return;
    }

    if (V1.size() < 10 || V2.size() < 10) {
        std::cout << "Каждый вектор должен содержать не менее 10 элементов.\n";
        return;
    }

    std::cout << "\nПервый вектор до преобразования: ";
    bool first = true;
    printRange(V1.begin(), V1.end(), first);
    std::cout << '\n';

    std::cout << "Второй вектор до преобразования: ";
    first = true;
    printRange(V2.begin(), V2.end(), first);
    std::cout << '\n';

    transformVectors(V1, V2, A, B);

    std::cout << "Первый вектор после преобразования: ";
    first = true;
    printRange(V1.begin(), V1.end(), first);
    std::cout << '\n';

    std::cout << "Второй вектор после преобразования: ";
    first = true;
    printRange(V2.begin(), V2.end(), first);
    std::cout << '\n';
}