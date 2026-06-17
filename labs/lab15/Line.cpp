#include "Line.h"
#include <cmath>
#include <sstream>

Line::Line(const Point& start, const Point& end) : start(start), end(end) {}

Line::Line(double x1, double y1, double x2, double y2) 
    : start(Point(x1, y1)), end(Point(x2, y2)) {}

Line::Line() : start(Point()), end(Point()) {}

const Point& Line::getStart() const {
    return start;
}

const Point& Line::getEnd() const {
    return end;
}

void Line::setStart(const Point& start) {
    this->start = start;
}

void Line::setEnd(const Point& end) {
    this->end = end;
}

std::string Line::toString() const {
    return "Линия от " + start.toString() + " до " + end.toString();
}

int Line::getLength() const {
    return static_cast<int>(start.distanceTo(end));
}