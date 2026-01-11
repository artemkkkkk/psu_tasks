#include "student_sort.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool compareSurname(const Student& a, const Student& b) {
    return a.surname < b.surname;
}

void quickSortStudents(std::vector<Student>& arr, int left, int right) {
    if (left >= right) return;
    int i = left, j = right;
    Student pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i].surname < pivot.surname) ++i;
        while (arr[j].surname > pivot.surname) --j;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            ++i; --j;
        }
    }

    if (left < j) quickSortStudents(arr, left, j);
    if (i < right) quickSortStudents(arr, i, right);
}

void sortStudentsFromFile(const std::string& inF, const std::string& outF) {
    std::ifstream fin(inF);
    if (!fin) {
        std::cerr << "Не удалось открыть файл " << inF << "\n";
        return;
    }

    std::vector<Student> students;
    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        Student s;
        if (iss >> s.surname >> s.score) {
            students.push_back(s);
        }
    }
    fin.close();

    quickSortStudents(students, 0, static_cast<int>(students.size()) - 1);

    std::ofstream fout(outF);
    for (const auto& s : students) {
        fout.width(15);
        fout << std::left << s.surname;
        fout.width(3);
        fout << std::right << s.score << "\n";
    }
    fout.close();
    std::cout << "Результат записан в " << outF << "\n";
}