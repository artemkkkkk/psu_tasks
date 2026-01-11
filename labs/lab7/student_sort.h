#ifndef STUDENT_SORT_H
#define STUDENT_SORT_H

#include <string>
#include <vector>

struct Student {
    std::string surname;
    int score;
};

void quickSortStudents(std::vector<Student>& students, int left, int right);
void sortStudentsFromFile(const std::string& inputFilename, const std::string& outputFilename);

#endif // STUDENT_SORT_H