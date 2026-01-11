#include "sort1.h"
#include <fstream>
#include <iostream>

void bubbleSortStart(std::vector<int>& arr, const std::string& filename) {
    std::ofstream log(filename);
    int n = static_cast<int>(arr.size());

    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = n - 1; j > i; --j) {
            if (arr[j - 1] > arr[j]) {
                std::swap(arr[j - 1], arr[j]);
                swapped = true;
            }
        }

        // Вывод после i+1 итерации (первые i+1 элементов отсортированы)
        for (int k = 0; k < n; ++k) {
            log << arr[k];
            if (k == i) log << " |";
            if (k != n - 1) log << " ";
        }
        log << "\n";

        if (!swapped) break;
    }
    log.close();
    std::cout << "Протокол сортировки записан в " << filename << "\n";
}