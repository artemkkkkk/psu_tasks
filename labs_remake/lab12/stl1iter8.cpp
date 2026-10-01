#include "stl1iter8.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>

static bool stringsEqual(const char* a, const char* b) {
    int i = 0;

    while (a[i] && b[i] && a[i] == b[i]) {
        ++i;
    }

    return a[i] == b[i];
}

static bool processFile(const char* inputName, const char* outputName, int K) {
    std::ifstream in(inputName);
    if (!in) {
        return false;
    }

    std::ofstream out(outputName);
    if (!out) {
        return false;
    }

    std::istream_iterator<std::string> inIt(in);
    std::istream_iterator<std::string> inEnd;

    std::ostream_iterator<std::string> outIt(out, "\n");

    std::remove_copy_if(
        inIt,
        inEnd,
        outIt,
        [K](const std::string& s) {
            return s.size() > static_cast<std::string::size_type>(K);
        }
    );

    return true;
}

static bool inputManual(int& K) {
    if (!readInt("Длина слова K: ", 1, 100, K)) {
        return false;
    }

    int count = 0;
    if (!readInt("Количество слов: ", 1, 50, count)) {
        return false;
    }

    std::ofstream out("input_stl1iter8.txt");
    if (!out) {
        std::cout << "Не удалось создать входной файл.\n";
        return false;
    }

    std::cout << "Введите слова по одному:\n";

    for (int i = 0; i < count; ++i) {
        std::cout << "Слово " << (i + 1) << ": ";

        std::string word;

        if (!(std::cin >> word)) {
            if (std::cin.eof()) {
                return false;
            }

            std::cin.clear();
            std::cin.ignore(1000000, '\n');
            --i;
            continue;
        }

        out << word << '\n';
    }

    std::cin.ignore(1000000, '\n');
    return true;
}

static bool inputRandom(int& K) {
    initRandom();

    static const char* words[] = {
        "cat",
        "dog",
        "bird",
        "fish",
        "lion",
        "mouse",
        "elephant",
        "ant",
        "fox",
        "wolf"
    };

    K = randomInt(2, 8);
    int count = randomInt(6, 10);

    std::ofstream out("input_stl1iter8.txt");
    if (!out) {
        std::cout << "Не удалось создать входной файл.\n";
        return false;
    }

    std::cout << "\nСлучайные данные:\n";
    std::cout << "K = " << K << '\n';
    std::cout << "Слова: ";

    for (int i = 0; i < count; ++i) {
        const char* word = words[randomInt(0, 9)];
        out << word << '\n';
        std::cout << word << ' ';
    }

    std::cout << '\n';
    return true;
}

static bool inputFile(char* inputName, char* outputName, int& K) {
    if (!readFileName("Введите имя входного файла: ", inputName, 256)) {
        return false;
    }

    if (!readFileName("Введите имя выходного файла: ", outputName, 256)) {
        return false;
    }

    if (stringsEqual(inputName, outputName)) {
        std::cout << "Имена входного и выходного файлов должны различаться.\n";
        return false;
    }

    if (!readInt("Длина слова K: ", 1, 100, K)) {
        return false;
    }

    return true;
}

void runSTL1Iter8(int mode) {
    char inputName[256];
    char outputName[256];
    int K = 0;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(K);
        copyString(inputName, 256, "input_stl1iter8.txt");
        copyString(outputName, 256, "output_stl1iter8.txt");
    } else if (mode == 2) {
        ok = inputRandom(K);
        copyString(inputName, 256, "input_stl1iter8.txt");
        copyString(outputName, 256, "output_stl1iter8.txt");
    } else if (mode == 3) {
        ok = inputFile(inputName, outputName, K);
    }

    if (!ok) {
        return;
    }

    if (!processFile(inputName, outputName, K)) {
        std::cout << "Не удалось обработать файл.\n";
        return;
    }

    std::cout << "\nРезультат записан в файл: " << outputName << '\n';

    std::ifstream result(outputName);
    if (result) {
        std::cout << "Слова, длина которых не превосходит " << K << ":\n";

        std::copy(
            std::istream_iterator<std::string>(result),
            std::istream_iterator<std::string>(),
            std::ostream_iterator<std::string>(std::cout, "\n")
        );
    }
}