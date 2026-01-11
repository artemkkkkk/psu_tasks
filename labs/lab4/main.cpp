#include <iostream>
#include <vector>
#include <string>
#include "array_io.h"
#include "tasks.h"

#ifdef _WIN32
#include <windows.h>
#endif


int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    int choice;
    std::vector<std::vector<int>> matrix;
    int rows, cols;

    std::cout << "=== Лабораторная работа №4 (Вариант 1) ===\n";

    // Создание матрицы
    std::cout << "Введите размеры матрицы (M N): ";
    std::cin >> rows >> cols;
    matrix = createMatrix(rows, cols);

    std::cout << "Как заполнить матрицу?\n";
    std::cout << "1. Случайными числами\n";
    std::cout << "2. С клавиатуры\n";
    std::cout << "3. Из файла\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;

    try {
        switch (choice) {
            case 1: fillRandom(matrix); break;
            case 2: fillFromConsole(matrix); break;
            case 3: {
                std::string fname;
                std::cout << "Имя файла: "; std::cin >> fname;
                fillFromFile(matrix, fname);
                break;
            }
            default: throw std::runtime_error("Неверный выбор");
        }

        std::cout << "\nИсходная матрица:\n";
        printToConsole(matrix);

        // Задача 1: Matrix25
        auto [rowIdx, rowSum] = findRowWithMaxSum(matrix);
        std::cout << "\n[Matrix25] Строка с макс. суммой: " << rowIdx << ", сумма = " << rowSum << "\n";

        // Задача 2: Matrix60
        auto mirrored = matrix;
        mirrorVertical(mirrored);
        std::cout << "\n[Matrix60] Матрица после вертикального отражения:\n";
        printToConsole(mirrored);

        // Задача 3: DArray1 (только если квадратная!)
        if (rows == cols && rows > 0) {
            int k1, k2;
            std::cout << "\n[DArray1] Введите k1 и k2 (0 ≤ k1 ≤ k2 < " << rows << "): ";
            std::cin >> k1 >> k2;
            auto sums = computeSums(matrix, k1, k2);
            std::cout << "S1 (строки " << k1 << "-" << k2 << ") = " << sums.S1 << "\n";
            std::cout << "S2 (столбцы " << k1 << "-" << k2 << ") = " << sums.S2 << "\n";
            std::cout << "S3 (главная диагональ) = " << sums.S3 << "\n";
            std::cout << "S4 (побочная диагональ) = " << sums.S4 << "\n";
        } else {
            std::cout << "\n[DArray1] Пропущено: требуется квадратная матрица.\n";
        }

        // Задача 4: DArray11
        auto maxInfo = findFirstMax(matrix);
        std::cout << "\n[DArray11] Первый максимальный элемент: " << maxInfo.value
             << " на позиции [" << maxInfo.row << "][" << maxInfo.col << "]\n";

        // Сохранить результат?
        std::cout << "\nСохранить исходную и отражённую матрицы в файлы? (y/n): ";
        char ans; std::cin >> ans;
        if (ans == 'y' || ans == 'Y') {
            printToFile(matrix, "original_matrix.txt");
            printToFile(mirrored, "mirrored_matrix.txt");
            std::cout << "Файлы сохранены: original_matrix.txt, mirrored_matrix.txt\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\n";
    std::cout << "≽^•⩊•^≼ \n\n";
    std::cout << "Введите любой символ для завершения \n";
    std::cin >> choice;
    return 0;
}