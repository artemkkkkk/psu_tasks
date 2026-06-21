#pragma once
#include "Point.h"
#include <string>

class Line {
private:
    Point start;
    Point end;

public:
    Line(const Point& start, const Point& end);
    Line(double x1, double y1, double x2, double y2);
    Line();

    const Point& getStart() const;
    const Point& getEnd() const;
    void setStart(const Point& start);
    void setEnd(const Point& end);

    std::string toString() const;
    int getLength() const;
};