#include <iostream>

int main() {
    int value;
    std::cout << "Введите значение члена ряда Фибоначчи: ";
    std::cin >> value;

    if (value < 0) {
        std::cout << "Члены ряда Фибоначчи неотрицательны. Введите неотрицательное число." << std::endl;
        return 1;
    }

    if (value == 0) {
        std::cout << "Номер члена: 0" << std::endl;
        return 0;
    }

    int prev = 0, curr = 1;
    int index = 1;

    while (curr < value) {
        int next = prev + curr;
        prev = curr;
        curr = next;
        index++;
    }

    if (curr == value) {
        std::cout << "Номер члена ряда Фибоначчи: " << index << std::endl;
    } else {
        std::cout << "Значение " << value << " не является членом ряда Фибоначчи." << std::endl;
    }

    return 0;
}