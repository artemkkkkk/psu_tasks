#ifndef MAGIC_SQUARE_H_
#define MAGIC_SQUARE_H_

#include <vector>
#include <string>

/**
 * Генерирует магический квадрат нечётного порядка методом Сиама.
 * @param n Порядок квадрата (должен быть нечётным и > 0).
 * @return Двумерный вектор — магический квадрат.
 * @throws std::invalid_argument если n чётное или <= 0.
 */
std::vector<std::vector<int>> GenerateMagicSquare(int n);

/**
 * Проверяет, является ли переданный квадрат магическим.
 * Учитывает: уникальность чисел, суммы строк/столбцов/диагоналей.
 * @param square Квадратная матрица.
 * @return true, если квадрат магический.
 */
bool IsMagicSquare(const std::vector<std::vector<int>>& square);

/**
 * Возвращает сумму магического квадрата порядка n.
 */
int GetMagicSum(int n);

/**
 * Получает суммы всех строк.
 */
std::vector<int> GetRowSums(const std::vector<std::vector<int>>& square);

/**
 * Получает суммы всех столбцов.
 */
std::vector<int> GetColumnSums(const std::vector<std::vector<int>>& square);

/**
 * Получает суммы главной и побочной диагоналей.
 * @return pair<main_diag, anti_diag>
 */
std::pair<int, int> GetDiagonalSums(const std::vector<std::vector<int>>& square);

/**
 * Проверяет уникальность всех элементов в квадрате.
 */
bool HasUniqueNumbers(const std::vector<std::vector<int>>& square);

#endif // MAGIC_SQUARE_H_