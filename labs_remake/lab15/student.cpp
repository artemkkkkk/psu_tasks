#include "student.h"
#include <iostream>
#include <cstdio>

void Student::copyName(char* dest, const char* src) {
    if (!dest) {
        return;
    }

    if (!src) {
        dest[0] = '\0';
        return;
    }

    int i = 0;
    while (i < 63 && src[i]) {
        dest[i] = src[i];
        ++i;
    }

    dest[i] = '\0';
}

void Student::copyGrades(const int* source, int sourceCount) {
    delete[] grades;
    grades = 0;
    count = 0;

    if (sourceCount > 0 && source) {
        grades = new int[sourceCount];

        for (int i = 0; i < sourceCount; ++i) {
            grades[i] = source[i];
        }

        count = sourceCount;
    }
}

Student::Student(const char* studentName) : grades(0), count(0) {
    copyName(name, studentName);
}

Student::Student(const char* studentName, const int* initialGrades, int initialCount)
    : grades(0), count(0) {
    copyName(name, studentName);
    copyGrades(initialGrades, initialCount);
}

Student::Student(const Student& other) : grades(0), count(0) {
    copyName(name, other.name);
    copyGrades(other.grades, other.count);
}

Student::~Student() {
    delete[] grades;
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        copyName(name, other.name);
        copyGrades(other.grades, other.count);
    }

    return *this;
}

const char* Student::getName() const {
    return name;
}

int Student::getCount() const {
    return count;
}

int Student::getGrade(int index) const {
    if (index < 0 || index >= count) {
        return 0;
    }

    return grades[index];
}

bool Student::setGrade(int index, int value) {
    if (index < 0 || index >= count) {
        return false;
    }

    grades[index] = value;
    return true;
}

void Student::copyGradesFrom(const Student& other) {
    copyGrades(other.grades, other.count);
}

void Student::toString(char* buffer, int bufferSize) const {
    if (!buffer || bufferSize <= 0) {
        return;
    }

    int pos = std::snprintf(buffer, bufferSize, "%s:[", name);

    if (pos < 0) {
        return;
    }

    for (int i = 0; i < count; ++i) {
        if (pos >= bufferSize) {
            break;
        }

        if (i > 0) {
            pos += std::snprintf(buffer + pos, bufferSize - pos, ", ");
        }

        if (pos >= bufferSize) {
            break;
        }

        pos += std::snprintf(buffer + pos, bufferSize - pos, "%d", grades[i]);
    }

    if (pos < bufferSize) {
        std::snprintf(buffer + pos, bufferSize - pos, "]");
    }
}

void Student::print() const {
    char buffer[512];
    toString(buffer, 512);
    std::cout << buffer << '\n';
}