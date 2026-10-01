#include "line.h"
#include <iostream>
#include <cstdio>
#include <cmath>

Line::Line(Point startPoint, Point endPoint) : start(startPoint), end(endPoint) {}

Line::Line(int x1, int y1, int x2, int y2) : start(x1, y1), end(x2, y2) {}

Point Line::getStart() const {
    return start;
}

Point Line::getEnd() const {
    return end;
}

void Line::setStart(Point startPoint) {
    start = startPoint;
}

void Line::setEnd(Point endPoint) {
    end = endPoint;
}

void Line::setCoordinates(int x1, int y1, int x2, int y2) {
    start = Point(x1, y1);
    end = Point(x2, y2);
}

void Line::toString(char* buffer, int bufferSize) const {
    if (!buffer || bufferSize <= 0) {
        return;
    }

    char startBuffer[64];
    char endBuffer[64];

    start.toString(startBuffer, 64);
    end.toString(endBuffer, 64);

    std::snprintf(buffer, bufferSize, "Линия от %s до %s", startBuffer, endBuffer);
}

void Line::print() const {
    char buffer[256];
    toString(buffer, 256);
    std::cout << buffer << '\n';
}

int Line::length() const {
    double dx = static_cast<double>(end.getX() - start.getX());
    double dy = static_cast<double>(end.getY() - start.getY());

    double result = std::sqrt(dx * dx + dy * dy);
    return static_cast<int>(result + 0.5);
}