#include "array_io.h"
#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <ctime>

std::vector<std::vector<int>> createMatrix(int rows, int cols) {
    return std::vector<std::vector<int>>(rows, std::vector<int>(cols));
}

void fillRandom(std::vector<std::vector<int>>& mat, int minVal, int maxVal) {
    static std::mt19937 gen(static_cast<unsigned>(std::time(0)));
    std::uniform_int_distribution<> dis(minVal, maxVal);
    for (auto& row : mat)
        for (int& el : row)
            el = dis(gen);
}

void fillFromConsole(std::vector<std::vector<int>>& mat) {
    for (size_t i = 0; i < mat.size(); ++i)
        for (size_t j = 0; j < mat[i].size(); ++j)
            std::cin >> mat[i][j];
}

void fillFromFile(std::vector<std::vector<int>>& mat, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    for (auto& row : mat)
        for (int& el : row)
            fin >> el;
    fin.close();
}

void printToConsole(const std::vector<std::vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int el : row)
            std::cout << el << "\t";
        std::cout << "\n";
    }
}

void printToFile(const std::vector<std::vector<int>>& mat, const std::string& filename) {
    std::ofstream fout(filename);
    for (const auto& row : mat) {
        for (int el : row)
            fout << el << "\t";
        fout << "\n";
    }
    fout.close();
}