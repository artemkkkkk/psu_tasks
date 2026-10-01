#ifndef TIME_H
#define TIME_H

#include <iosfwd>

class Time {
private:
    unsigned char hours;
    unsigned char minutes;

    unsigned totalMinutes() const;
    void setTotal(unsigned total);
    static unsigned normalize(unsigned total);

public:
    Time();
    Time(unsigned char h, unsigned char m);
    explicit Time(unsigned totalMinutes);

    unsigned char getHours() const;
    unsigned char getMinutes() const;

    Time addMinutes(unsigned m) const;

    Time& operator++();
    Time operator++(int);
    Time& operator--();
    Time operator--(int);

    explicit operator short int() const;
    operator bool() const;

    Time operator+(unsigned m) const;
    Time operator-(unsigned m) const;

    friend std::ostream& operator<<(std::ostream& out, const Time& t);
};

#endif