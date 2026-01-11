#include "exam_task.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

void solveExamTaskC13() {
    int K, N;
    std::cout << "[ExamTaskC13] Введите код клиента K: ";
    std::cin >> K;
    std::cout << "Введите количество записей N: ";
    std::cin >> N;

    if (N <= 0) {
        std::cout << "Нет данных для обработки.\n";
        return;
    }

    std::cout << "\nВведите " << N << " записей в формате:\n";
    std::cout << "<Продолжительность> <Год> <Номер месяца> <Код клиента>\n";
    std::cout << "Пример: 12 2005 3 42\n";
    std::cout << "Ограничения:\n";
    std::cout << "- Продолжительность: от 1 до 30 (часы)\n";
    std::cout << "- Год: от 2000 до 2010\n";
    std::cout << "- Месяц: от 1 до 12\n";
    std::cout << "- Код клиента: от 10 до 99\n\n";

    std::vector<Record> records(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> records[i].duration
                 >> records[i].year
                 >> records[i].month
                 >> records[i].clientCode;
    }

    // Группировка по годам: для каждого года — лучший месяц
    std::map<int, std::pair<int, int>> bestMonth; // год -> {продолжительность, месяц}

    for (const auto& r : records) {
        if (r.clientCode != K) continue;
        if (bestMonth.count(r.year)) {
            auto& [bestDur, bestMon] = bestMonth[r.year];
            if (r.duration > bestDur ||
                (r.duration == bestDur && r.month < bestMon)) {
                bestDur = r.duration;
                bestMon = r.month;
                }
        } else {
            bestMonth[r.year] = {r.duration, r.month};
        }
    }

    if (bestMonth.empty()) {
        std::cout << "Нет данных\n";
        return;
    }

    // Вывод по убыванию года
    std::vector<int> years;
    for (const auto& p : bestMonth) years.push_back(p.first);
    std::sort(years.rbegin(), years.rend());

    for (int y : years) {
        std::cout << y << " "
                  << bestMonth[y].second << " "
                  << bestMonth[y].first << "\n";
    }
}