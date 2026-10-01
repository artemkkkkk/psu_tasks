#include "homedyn1.h"
#include "utils.h"
#include <iostream>
#include <fstream>

static const int MAX_BOARD = 80;

static bool inputManual(int board[][MAX_BOARD], int& N) {
    if (!readInt("Размер доски N: ", 2, 79, N)) {
        return false;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << "Значение строка " << (i + 1) << ", столбец " << (j + 1) << ": ";
            if (!readIntNoPrompt(0, 100, board[i][j])) {
                return false;
            }
        }
    }

    return true;
}

static bool inputRandom(int board[][MAX_BOARD], int& N) {
    initRandom();

    N = randomInt(3, 7);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = randomInt(0, 100);
        }
    }

    std::cout << "\nСлучайная доска:\n";

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return true;
}

static bool inputFile(int board[][MAX_BOARD], int& N) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);

    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    if (!(in >> N)) {
        std::cout << "Не удалось прочитать размер доски.\n";
        return false;
    }

    if (N < 2 || N >= MAX_BOARD) {
        std::cout << "Некорректный размер доски.\n";
        return false;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int x = 0;

            if (!(in >> x)) {
                std::cout << "Не удалось прочитать данные доски.\n";
                return false;
            }

            if (x < 0 || x > 100) {
                std::cout << "Значения на доске должны быть от 0 до 100.\n";
                return false;
            }

            board[i][j] = x;
        }
    }

    std::cout << "Загружено из файла: N = " << N << '\n';
    return true;
}

static bool solveHomeDyn1(const int board[][MAX_BOARD], int N, long long& result) {
    if (N < 2 || N >= MAX_BOARD) {
        return false;
    }

    long long dp[MAX_BOARD][MAX_BOARD];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dp[i][j] = -1;
        }
    }

    dp[0][N - 1] = board[0][N - 1];

    for (int i = 0; i < N; ++i) {
        for (int j = N - 1; j >= 0; --j) {
            if (i == 0 && j == N - 1) {
                continue;
            }

            long long best = -1;

            if (i > 0 && dp[i - 1][j] != -1) {
                best = dp[i - 1][j];
            }

            if (j + 1 < N && dp[i][j + 1] != -1 && dp[i][j + 1] > best) {
                best = dp[i][j + 1];
            }

            if (best != -1) {
                dp[i][j] = best + board[i][j];
            }
        }
    }

    result = dp[N - 1][0];
    return result != -1;
}

static void printHomeDyn1Result(bool solved, long long result) {
    std::ofstream out("output_homedyn1.txt");

    std::cout << "\nРезультат:\n";

    if (!solved) {
        std::cout << "Не удалось найти путь.\n";

        if (out) {
            out << "-\n";
        }

        return;
    }

    std::cout << "Максимальная сумма: " << result << '\n';

    if (out) {
        out << result << '\n';
    }
}

void runHomeDyn1(int mode) {
    int board[MAX_BOARD][MAX_BOARD];
    int N = 0;

    bool inputOk = false;

    if (mode == 1) {
        inputOk = inputManual(board, N);
    } else if (mode == 2) {
        inputOk = inputRandom(board, N);
    } else if (mode == 3) {
        inputOk = inputFile(board, N);
    }

    if (!inputOk) {
        return;
    }

    long long result = 0;
    bool solved = solveHomeDyn1(board, N, result);

    printHomeDyn1Result(solved, result);
}