#include <iostream>
#include "exam_task.h"
#include "shapes.h"
#include "cars.h"

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
        std::cout << "\n=== Лабораторная №6 (Вариант 1) ===\n";
        std::cout << "1. ExamTaskC1 — фитнес-центр\n";
        std::cout << "2. Фигуры\n";
        std::cout << "3. Автомобили\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите задачу: ";
        std::cin >> task;

        switch (task) {
            case 1:
                solveExamTaskC1();
                break;
            case 2: {
                int N;
                std::cout << "Сколько фигур ввести? "; std::cin >> N;
                if (N <= 0) break;
                Figure* figs = new Figure[N];
                for (int i = 0; i < N; ++i) {
                    std::cout << "\nФигура " << (i + 1) << ":\n";
                    inputFigure(figs[i]);
                }
                saveFiguresToFile(figs, N, "figures.txt");
                printFiguresTable(figs, N);
                delete[] figs;
                std::cout << "Данные сохранены в figures.txt\n";
                break;
            }
            case 3:
                runCarManager();
                break;
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