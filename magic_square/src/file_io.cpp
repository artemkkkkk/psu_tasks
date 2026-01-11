#include "../include/file_io.h"
#include <fstream>
#include <iomanip>
#include <iostream>

bool SaveSquareToFile(const std::vector<std::vector<int>>& square,
                      const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    int n = square.size();
    if (n == 0) {
        file.close();
        return true;
    }

    int max_val = n * n;
    int width = static_cast<int>(std::to_string(max_val).length()) + 1;

    for (const auto& row : square) {
        for (int val : row) {
            file << std::setw(width) << val;
        }
        file << '\n';
    }

    file.close();
    return true;
}