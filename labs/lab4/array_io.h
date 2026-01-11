#ifndef ARRAY_IO_H
#define ARRAY_IO_H

#include <vector>
#include <string>

// Ввод
void fillRandom(std::vector<std::vector<int>>& mat, int minVal = -10, int maxVal = 10);
void fillFromConsole(std::vector<std::vector<int>>& mat);
void fillFromFile(std::vector<std::vector<int>>& mat, const std::string& filename);

// Вывод
void printToConsole(const std::vector<std::vector<int>>& mat);
void printToFile(const std::vector<std::vector<int>>& mat, const std::string& filename);

// Утилиты
std::vector<std::vector<int>> createMatrix(int rows, int cols);

#endif // ARRAY_IO_H