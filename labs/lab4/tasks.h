#ifndef TASKS_H
#define TASKS_H

#include <vector>

// Matrix25
std::pair<int, long long> findRowWithMaxSum(const std::vector<std::vector<int>>& mat);

// Matrix60
void mirrorVertical(std::vector<std::vector<int>>& mat);

// DArray1
struct SumsResult {
    long long S1 = 0, S2 = 0, S3 = 0, S4 = 0;
};
SumsResult computeSums(const std::vector<std::vector<int>>& mat, int k1, int k2);

// DArray11
struct MaxElementInfo {
    int value;
    int row, col;
};
MaxElementInfo findFirstMax(const std::vector<std::vector<int>>& mat);

#endif // TASKS_H