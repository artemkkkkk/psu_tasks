#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line {
private:
    Point start;
    Point end;

public:
    Line(Point startPoint, Point endPoint);
    Line(int x1, int y1, int x2, int y2);

    Point getStart() const;
    Point getEnd() const;

    void setStart(Point startPoint);
    void setEnd(Point endPoint);
    void setCoordinates(int x1, int y1, int x2, int y2);

    void toString(char* buffer, int bufferSize) const;
    void print() const;

    int length() const;
};

#endif