#ifndef STUDENT_H
#define STUDENT_H

class Student {
private:
    char name[64];
    int* grades;
    int count;

    static void copyName(char* dest, const char* src);
    void copyGrades(const int* source, int sourceCount);

public:
    Student(const char* studentName);
    Student(const char* studentName, const int* initialGrades, int initialCount);
    Student(const Student& other);
    ~Student();

    Student& operator=(const Student& other);

    const char* getName() const;
    int getCount() const;

    int getGrade(int index) const;
    bool setGrade(int index, int value);

    void copyGradesFrom(const Student& other);

    void toString(char* buffer, int bufferSize) const;
    void print() const;
};

#endif