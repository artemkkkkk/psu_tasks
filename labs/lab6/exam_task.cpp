#include "exam_task.h"
#include <iostream>
#include <vector>
#include <climits>

void solveExamTaskC1() {
    int N;
    std::cout << "[ExamTaskC1] Введите количество записей N: ";
    std::cin >> N;

    if (N <= 0) {
        std::cout << "Нет данных.\n";
        return;
    }

    std::cout << "Введите " << N << " записей в формате:\n";
    std::cout << "<Код клиента> <Год> <Номер месяца> <Продолжительность занятий (в часах)>\n";
    std::cout << "Пример: 42 2005 3 12\n";
    std::cout << "Диапазоны: код — от 10 до 99, год — от 2000 до 2010, месяц — от 1 до 12, продолжительность — от 1 до 30.\n";

    std::vector<FitnessRecord> records(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> records[i].clientCode
                 >> records[i].year
                 >> records[i].month
                 >> records[i].duration;
    }

    int minDuration = INT_MAX;
    int bestYear = 0, bestMonth = 0;

    // Проходим с конца, чтобы выбрать последнюю при равенстве
    for (int i = N - 1; i >= 0; --i) {
        if (records[i].duration < minDuration) {
            minDuration = records[i].duration;
            bestYear = records[i].year;
            bestMonth = records[i].month;
        }
    }

    std::cout << "Мин. продолжительность: " << minDuration << "\n";
    std::cout << "Год: " << bestYear << ", Месяц: " << bestMonth << "\n";
}