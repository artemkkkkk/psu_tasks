#include <iostream>
#include <vector>
#include "sort1.h"
#include "exam_task.h"
#include "student_sort.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    int task;
    do {
        std::cout << "\n=== Лабораторная работа №7 (Вариант 1) ===\n";
        std::cout << "1. Sort1 — сортировка пузырьком (в начало)\n";
        std::cout << "2. ExamTaskC13 — анализ фитнес-данных\n";
        std::cout << "3. Five11 — сортировка учеников по фамилии (быстрая)\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите задачу: ";
        std::cin >> task;

        switch (task) {
            case 1: {
                int N;
                std::cout << "Введите N: ";
                std::cin >> N;
                std::vector<int> arr(N);
                std::cout << "Введите " << N << " целых чисел:\n";
                for (int i = 0; i < N; ++i) std::cin >> arr[i];
                bubbleSortStart(arr, "sort1_log.txt");
                break;
            }
            case 2:
                solveExamTaskC13();
                break;
            case 3: {
                std::string inF, outF;
                std::cout << "Имя входного файла (например, students.txt): ";
                std::cin >> inF;
                std::cout << "Имя выходного файла: ";
                std::cin >> outF;
                sortStudentsFromFile(inF, outF);
                break;
            }
            case 0:
                std::cout << "Выход...\n";
                break;
            default:
                std::cout << "Неверный выбор.\n";
        }
    } while (task != 0);

    std::cout << "\n";
    std::cout << "≽^•⩊•^≼ \n\n";
    std::cout << "Введите любой символ для завершения \n";
    std::cin >> task;
    return 0;
}