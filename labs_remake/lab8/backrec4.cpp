#include "backrec4.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <new>

static const int MAX_MANUAL_N = 60;
static const int MAX_FILE_N = 100000;
static const int MAX_MANUAL_VALUE = 100000;
static const int MAX_DP_B = 1000000;
static const long long MAX_CHOICE_SIZE = 20000000LL;

struct DfsState {
    const int* c;
    const int* d;
    int N;
    int A;
    int B;
    long long bestVolume;
    int bestWeight;
    bool* bestSelected;
    bool* currentSelected;
    long long* suffixWeight;
    bool found;
};

static void dfsStep(DfsState* s, int idx, long long weight, long long volume) {
    if (weight > s->B) {
        return;
    }

    if (s->found && volume > s->bestVolume) {
        return;
    }

    if (weight + s->suffixWeight[idx] < s->A) {
        return;
    }

    if (weight >= s->A) {
        if (!s->found || volume < s->bestVolume) {
            s->found = true;
            s->bestVolume = volume;
            s->bestWeight = static_cast<int>(weight);

            for (int i = 0; i < s->N; ++i) {
                s->bestSelected[i] = s->currentSelected[i];
            }
        }
        return;
    }

    if (idx == s->N) {
        return;
    }

    s->currentSelected[idx] = true;
    dfsStep(s, idx + 1, weight + s->c[idx], volume + s->d[idx]);
    s->currentSelected[idx] = false;
    dfsStep(s, idx + 1, weight, volume);
}

static bool solveDFS(
    const int* c,
    const int* d,
    int N,
    int A,
    int B,
    bool* selected,
    int& totalWeight,
    long long& totalVolume
) {
    if (N <= 0 || A < 0 || B < A) {
        return false;
    }

    long long* suffixWeight = new (std::nothrow) long long[N + 1];
    bool* currentSelected = new (std::nothrow) bool[N];
    bool* bestSelected = new (std::nothrow) bool[N];

    if (!suffixWeight || !currentSelected || !bestSelected) {
        delete[] suffixWeight;
        delete[] currentSelected;
        delete[] bestSelected;
        return false;
    }

    suffixWeight[N] = 0;
    for (int i = N - 1; i >= 0; --i) {
        suffixWeight[i] = suffixWeight[i + 1] + c[i];
    }

    if (suffixWeight[0] < A) {
        delete[] suffixWeight;
        delete[] currentSelected;
        delete[] bestSelected;
        return false;
    }

    for (int i = 0; i < N; ++i) {
        currentSelected[i] = false;
        bestSelected[i] = false;
        selected[i] = false;
    }

    DfsState state;
    state.c = c;
    state.d = d;
    state.N = N;
    state.A = A;
    state.B = B;
    state.bestVolume = 0;
    state.bestWeight = 0;
    state.bestSelected = bestSelected;
    state.currentSelected = currentSelected;
    state.suffixWeight = suffixWeight;
    state.found = false;

    dfsStep(&state, 0, 0, 0);

    if (state.found) {
        for (int i = 0; i < N; ++i) {
            selected[i] = bestSelected[i];
        }

        totalWeight = state.bestWeight;
        totalVolume = state.bestVolume;
    }

    delete[] suffixWeight;
    delete[] currentSelected;
    delete[] bestSelected;

    return state.found;
}

static bool solveDP(
    const int* c,
    const int* d,
    int N,
    int A,
    int B,
    bool* selected,
    int& totalWeight,
    long long& totalVolume
) {
    if (N < 0 || A < 0 || B < A || B > MAX_DP_B) {
        return false;
    }

    size_t width = static_cast<size_t>(B + 1);
    long long choiceSizeLL = static_cast<long long>(N + 1) * static_cast<long long>(B + 1);

    if (choiceSizeLL <= 0 || choiceSizeLL > MAX_CHOICE_SIZE) {
        return false;
    }

    size_t choiceSize = static_cast<size_t>(choiceSizeLL);

    long long* prev = new (std::nothrow) long long[width];
    long long* cur = new (std::nothrow) long long[width];
    char* choice = new (std::nothrow) char[choiceSize]();

    if (!prev || !cur || !choice) {
        delete[] prev;
        delete[] cur;
        delete[] choice;
        return false;
    }

    const long long INF = 4000000000000000000LL;

    for (int w = 0; w <= B; ++w) {
        prev[w] = INF;
    }

    prev[0] = 0;

    for (int i = 0; i < N; ++i) {
        for (int w = 0; w <= B; ++w) {
            cur[w] = prev[w];
        }

        int wi = c[i];
        int vi = d[i];

        if (wi >= 0 && wi <= B) {
            for (int w = wi; w <= B; ++w) {
                long long prevVal = prev[w - wi];
                if (prevVal == INF) {
                    continue;
                }

                long long add = static_cast<long long>(vi);
                long long val = INF;

                if (add >= 0 && prevVal <= INF - add) {
                    val = prevVal + add;
                } else if (add < 0) {
                    val = prevVal + add;
                }

                if (val < cur[w]) {
                    cur[w] = val;
                    choice[static_cast<size_t>(i + 1) * width + static_cast<size_t>(w)] = 1;
                }
            }
        }

        long long* temp = prev;
        prev = cur;
        cur = temp;
    }

    long long bestVolume = INF;
    int bestWeight = -1;

    for (int w = A; w <= B; ++w) {
        if (prev[w] < bestVolume) {
            bestVolume = prev[w];
            bestWeight = w;
        }
    }

    if (bestWeight < 0) {
        delete[] prev;
        delete[] cur;
        delete[] choice;
        return false;
    }

    for (int i = 0; i < N; ++i) {
        selected[i] = false;
    }

    int w = bestWeight;

    for (int i = N; i >= 1; --i) {
        size_t index = static_cast<size_t>(i) * width + static_cast<size_t>(w);

        if (choice[index]) {
            selected[i - 1] = true;
            w -= c[i - 1];

            if (w < 0) {
                break;
            }
        }
    }

    totalWeight = bestWeight;
    totalVolume = bestVolume;

    delete[] prev;
    delete[] cur;
    delete[] choice;

    return true;
}

static bool solveBackRec4(
    const int* c,
    const int* d,
    int N,
    int A,
    int B,
    bool* selected,
    int& totalWeight,
    long long& totalVolume
) {
    if (N <= 0 || A < 0 || B < A) {
        return false;
    }

    long long sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += c[i];
    }

    if (sum < A) {
        return false;
    }

    int effectiveB = B;
    if (sum < effectiveB) {
        effectiveB = static_cast<int>(sum);
    }

    if (effectiveB < A) {
        return false;
    }

    if (solveDP(c, d, N, A, effectiveB, selected, totalWeight, totalVolume)) {
        return true;
    }

    if (N <= 30) {
        return solveDFS(c, d, N, A, effectiveB, selected, totalWeight, totalVolume);
    }

    return false;
}

static bool inputManual(int*& c, int*& d, int& N, int& A, int& B) {
    if (!readInt("Количество артефактов: ", 1, MAX_MANUAL_N, N)) {
        return false;
    }

    if (!readInt("Минимальный вес A: ", 0, MAX_MANUAL_VALUE, A)) {
        return false;
    }

    if (!readInt("Максимальный вес B: ", A, MAX_MANUAL_VALUE, B)) {
        return false;
    }

    c = new (std::nothrow) int[N];
    d = new (std::nothrow) int[N];

    if (!c || !d) {
        delete[] c;
        delete[] d;
        c = 0;
        d = 0;
        return false;
    }

    for (int i = 0; i < N; ++i) {
        std::cout << "Вес " << (i + 1) << ": ";
        if (!readIntNoPrompt(0, MAX_MANUAL_VALUE, c[i])) {
            delete[] c;
            delete[] d;
            c = 0;
            d = 0;
            return false;
        }
    }

    for (int i = 0; i < N; ++i) {
        std::cout << "Объем " << (i + 1) << ": ";
        if (!readIntNoPrompt(0, MAX_MANUAL_VALUE, d[i])) {
            delete[] c;
            delete[] d;
            c = 0;
            d = 0;
            return false;
        }
    }

    return true;
}

static bool inputRandom(int*& c, int*& d, int& N, int& A, int& B) {
    initRandom();

    N = randomInt(5, 10);

    c = new (std::nothrow) int[N];
    d = new (std::nothrow) int[N];

    if (!c || !d) {
        delete[] c;
        delete[] d;
        c = 0;
        d = 0;
        return false;
    }

    int total = 0;

    for (int i = 0; i < N; ++i) {
        c[i] = randomInt(1, 20);
        total += c[i];
    }

    for (int i = 0; i < N; ++i) {
        d[i] = randomInt(1, 50);
    }

    A = total / 2;
    if (A < 1) {
        A = 1;
    }

    B = total;

    std::cout << "\nСлучайные данные:\n";
    std::cout << "N = " << N << ", A = " << A << ", B = " << B << '\n';

    std::cout << "Веса: ";
    for (int i = 0; i < N; ++i) {
        std::cout << c[i] << ' ';
    }
    std::cout << '\n';

    std::cout << "Объемы: ";
    for (int i = 0; i < N; ++i) {
        std::cout << d[i] << ' ';
    }
    std::cout << '\n';

    return true;
}

static bool readFromFile(const char* fileName, int*& c, int*& d, int& N, int& A, int& B) {
    std::ifstream in(fileName);

    if (!in) {
        return false;
    }

    if (!(in >> N >> A >> B)) {
        return false;
    }

    if (N <= 0 || N > MAX_FILE_N || A < 0 || B < A) {
        return false;
    }

    c = new (std::nothrow) int[N];
    d = new (std::nothrow) int[N];

    if (!c || !d) {
        delete[] c;
        delete[] d;
        c = 0;
        d = 0;
        return false;
    }

    for (int i = 0; i < N; ++i) {
        if (!(in >> c[i]) || c[i] < 0) {
            delete[] c;
            delete[] d;
            c = 0;
            d = 0;
            return false;
        }
    }

    for (int i = 0; i < N; ++i) {
        if (!(in >> d[i]) || d[i] < 0) {
            delete[] c;
            delete[] d;
            c = 0;
            d = 0;
            return false;
        }
    }

    return true;
}

static bool inputFile(int*& c, int*& d, int& N, int& A, int& B) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    if (!readFromFile(fileName, c, d, N, A, B)) {
        std::cout << "Не удалось прочитать файл или данные некорректны.\n";
        return false;
    }

    std::cout << "Загружено из файла: N = " << N << ", A = " << A << ", B = " << B << '\n';
    return true;
}

static void printBackRec4Result(
    bool solved,
    const bool* selected,
    int N,
    int totalWeight,
    long long totalVolume
) {
    std::ofstream out("output_backrec4.txt");

    std::cout << "\nРезультат:\n";

    if (!solved) {
        std::cout << "Решение не найдено.\n";

        if (out) {
            out << "-\n";
        }

        return;
    }

    std::cout << "Номера вещей: ";

    bool any = false;
    for (int i = 0; i < N; ++i) {
        if (selected[i]) {
            if (any) {
                std::cout << ' ';
            }

            std::cout << (i + 1);
            any = true;
        }
    }

    if (!any) {
        std::cout << '-';
    }

    std::cout << "\nСуммарный вес: " << totalWeight << '\n';
    std::cout << "Суммарный объем: " << totalVolume << '\n';

    if (out) {
        any = false;

        for (int i = 0; i < N; ++i) {
            if (selected[i]) {
                if (any) {
                    out << ' ';
                }

                out << (i + 1);
                any = true;
            }
        }

        if (!any) {
            out << '-';
        }

        out << '\n' << totalWeight << ' ' << totalVolume << '\n';
    }
}

void runBackRec4(int mode) {
    int* c = 0;
    int* d = 0;
    int N = 0;
    int A = 0;
    int B = 0;

    bool inputOk = false;

    if (mode == 1) {
        inputOk = inputManual(c, d, N, A, B);
    } else if (mode == 2) {
        inputOk = inputRandom(c, d, N, A, B);
    } else if (mode == 3) {
        inputOk = inputFile(c, d, N, A, B);
    }

    if (!inputOk) {
        return;
    }

    bool* selected = new (std::nothrow) bool[N];

    if (!selected) {
        delete[] c;
        delete[] d;
        return;
    }

    for (int i = 0; i < N; ++i) {
        selected[i] = false;
    }

    int totalWeight = 0;
    long long totalVolume = 0;

    bool solved = solveBackRec4(c, d, N, A, B, selected, totalWeight, totalVolume);

    printBackRec4Result(solved, selected, N, totalWeight, totalVolume);

    delete[] selected;
    delete[] c;
    delete[] d;
}