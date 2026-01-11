#include "tasks.h"
#include <stdexcept>
#include <climits>

// Matrix25
std::pair<int, long long> findRowWithMaxSum(const std::vector<std::vector<int>>& mat) {
    if (mat.empty()) throw std::invalid_argument("Матрица пуста");
    long long maxSum = LLONG_MIN;
    int bestRow = 0;
    for (size_t i = 0; i < mat.size(); ++i) {
        long long sum = 0;
        for (int x : mat[i]) sum += x;
        if (sum > maxSum) {
            maxSum = sum;
            bestRow = static_cast<int>(i);
        }
    }
    return {bestRow, maxSum};
}

// Matrix60
void mirrorVertical(std::vector<std::vector<int>>& mat) {
    for (auto& row : mat) {
        size_t n = row.size();
        for (size_t j = 0; j < n / 2; ++j) {
            std::swap(row[j], row[n - 1 - j]);
        }
    }
}

// DArray1
SumsResult computeSums(const std::vector<std::vector<int>>& mat, int k1, int k2) {
    int n = static_cast<int>(mat.size());
    if (n == 0 || mat[0].size() != static_cast<size_t>(n))
        throw std::invalid_argument("Требуется квадратная матрица");
    if (k1 < 0 || k2 >= n || k1 > k2)
        throw std::invalid_argument("Некорректные k1/k2");

    SumsResult res;

    // S1: строки k1..k2
    for (int i = k1; i <= k2; ++i)
        for (int x : mat[i]) res.S1 += x;

    // S2: столбцы k1..k2
    for (int j = k1; j <= k2; ++j)
        for (const auto& row : mat) res.S2 += row[j];

    // S3: главная диагональ
    for (int i = 0; i < n; ++i) res.S3 += mat[i][i];

    // S4: побочная диагональ
    for (int i = 0; i < n; ++i) res.S4 += mat[i][n - 1 - i];

    return res;
}

// DArray11
MaxElementInfo findFirstMax(const std::vector<std::vector<int>>& mat) {
    if (mat.empty() || mat[0].empty())
        throw std::invalid_argument("Матрица пуста");
    int maxValue = mat[0][0];
    int maxRow = 0, maxCol = 0;
    for (size_t i = 0; i < mat.size(); ++i) {
        for (size_t j = 0; j < mat[i].size(); ++j) {
            if (mat[i][j] > maxValue) {
                maxValue = mat[i][j];
                maxRow = static_cast<int>(i);
                maxCol = static_cast<int>(j);
            }
        }
    }
    return {maxValue, maxRow, maxCol};
}