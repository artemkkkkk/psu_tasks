#ifndef DEPENDENTLINE_H
#define DEPENDENTLINE_H

#include "line.h"

class DependentLine {
private:
    const Line* startSource;
    const Line* endSource;

public:
    DependentLine(const Line* startLine, const Line* endLine);

    Point getStart() const;
    Point getEnd() const;

    void toString(char* buffer, int bufferSize) const;
    void print() const;
};

#endif