#include "dependentline.h"
#include <iostream>
#include <cstdio>

DependentLine::DependentLine(const Line* startLine, const Line* endLine)
    : startSource(startLine), endSource(endLine) {}

Point DependentLine::getStart() const {
    if (!startSource) {
        return Point(0, 0);
    }

    return startSource->getStart();
}

Point DependentLine::getEnd() const {
    if (!endSource) {
        return Point(0, 0);
    }

    return endSource->getEnd();
}

void DependentLine::toString(char* buffer, int bufferSize) const {
    if (!buffer || bufferSize <= 0) {
        return;
    }

    Point startPoint = getStart();
    Point endPoint = getEnd();

    char startBuffer[64];
    char endBuffer[64];

    startPoint.toString(startBuffer, 64);
    endPoint.toString(endBuffer, 64);

    std::snprintf(buffer, bufferSize, "Линия от %s до %s", startBuffer, endBuffer);
}

void DependentLine::print() const {
    char buffer[256];
    toString(buffer, 256);
    std::cout << buffer << '\n';
}