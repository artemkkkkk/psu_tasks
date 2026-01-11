#include "../include/magic_square.h"
#include <unordered_set>
#include <numeric>
#include <stdexcept>
#include <cmath>

std::vector<std::vector<int>> GenerateMagicSquare(int n) {
    if (n <= 0 || n % 2 == 0) {
        throw std::invalid_argument("Order must be positive and odd.");
    }

    std::vector<std::vector<int>> square(n, std::vector<int>(n, 0));
    int num = 1;
    int row = 0;
    int col = n / 2;

    while (num <= n * n) {
        square[row][col] = num++;

        int next_row = (row - 1 + n) % n;
        int next_col = (col + 1) % n;

        if (square[next_row][next_col] != 0) {
            row = (row + 1) % n;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    return square;
}

int GetMagicSum(int n) {
    return n * (n * n + 1) / 2;
}

std::vector<int> GetRowSums(const std::vector<std::vector<int>>& square) {
    std::vector<int> sums;
    for (const auto& row : square) {
        sums.push_back(std::accumulate(row.begin(), row.end(), 0));
    }
    return sums;
}

std::vector<int> GetColumnSums(const std::vector<std::vector<int>>& square) {
    int n = square.size();
    std::vector<int> sums(n, 0);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            sums[j] += square[i][j];
        }
    }
    return sums;
}

std::pair<int, int> GetDiagonalSums(const std::vector<std::vector<int>>& square) {
    int n = square.size();
    int main_diag = 0;
    int anti_diag = 0;
    for (int i = 0; i < n; ++i) {
        main_diag += square[i][i];
        anti_diag += square[i][n - 1 - i];
    }
    return {main_diag, anti_diag};
}

bool HasUniqueNumbers(const std::vector<std::vector<int>>& square) {
    std::unordered_set<int> seen;
    for (const auto& row : square) {
        for (int val : row) {
            if (seen.find(val) != seen.end()) {
                return false;
            }
            seen.insert(val);
        }
    }
    return true;
}

bool IsMagicSquare(const std::vector<std::vector<int>>& square) {
    if (square.empty()) return false;
    int n = square.size();
    for (const auto& row : square) {
        if (static_cast<int>(row.size()) != n) return false;
    }

    int expected_sum = GetMagicSum(n);

    auto row_sums = GetRowSums(square);
    auto col_sums = GetColumnSums(square);
    auto diags = GetDiagonalSums(square);

    for (int s : row_sums) {
        if (s != expected_sum) return false;
    }
    for (int s : col_sums) {
        if (s != expected_sum) return false;
    }
    if (diags.first != expected_sum || diags.second != expected_sum) {
        return false;
    }

    return HasUniqueNumbers(square);
}