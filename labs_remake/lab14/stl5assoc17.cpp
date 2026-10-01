#include "stl5assoc17.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

static bool inputManual(std::vector<std::string>& V) {
    int count = 0;

    if (!readInt("Количество слов: ", 1, 30, count)) {
        return false;
    }

    V.clear();

    std::cout << "Вводите слова заглавными английскими буквами:\n";

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

        V.push_back(word);
    }

    std::cin.ignore(1000000, '\n');
    return true;
}

static bool inputRandom(std::vector<std::string>& V) {
    initRandom();

    static const char* words[] = {
        "APPLE",
        "APRICOT",
        "AVOCADO",
        "BANANA",
        "BLUEBERRY",
        "CHERRY",
        "DATE",
        "ELDERBERRY",
        "FIG",
        "GRAPE"
    };

    int wordCount = 10;
    int count = randomInt(6, 10);

    V.clear();

    for (int i = 0; i < count; ++i) {
        V.push_back(words[randomInt(0, wordCount - 1)]);
    }

    std::cout << "\nСлучайные данные:\n";

    for (std::vector<std::string>::const_iterator it = V.begin(); it != V.end(); ++it) {
        std::cout << *it << '\n';
    }

    return true;
}

static bool inputFile(std::vector<std::string>& V) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    int count = 0;
    if (!(in >> count)) {
        std::cout << "Не удалось прочитать количество слов.\n";
        return false;
    }

    if (count < 1 || count > 100000) {
        std::cout << "Некорректное количество слов.\n";
        return false;
    }

    V.clear();

    for (int i = 0; i < count; ++i) {
        std::string word;

        if (!(in >> word)) {
            std::cout << "Не удалось прочитать слова.\n";
            return false;
        }

        V.push_back(word);
    }

    return true;
}

static void buildMap(const std::vector<std::string>& V, std::map<char, int>& M) {
    M.clear();

    for (std::vector<std::string>::const_iterator it = V.begin(); it != V.end(); ++it) {
        M[(*it)[0]] += static_cast<int>(it->size());
    }
}

void runSTL5Assoc17(int mode) {
    std::vector<std::string> V;
    std::map<char, int> M;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(V);
    } else if (mode == 2) {
        ok = inputRandom(V);
    } else if (mode == 3) {
        ok = inputFile(V);
    }

    if (!ok) {
        return;
    }

    if (V.empty()) {
        std::cout << "Вектор слов пуст.\n";
        return;
    }

    buildMap(V, M);

    std::cout << "\nРезультат:\n";

    for (std::map<char, int>::const_iterator it = M.begin(); it != M.end(); ++it) {
        std::cout << it->first << ' ' << it->second << '\n';
    }
}