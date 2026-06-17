#pragma once
#include <iostream>

class Time {
private:
    unsigned char hours;
    unsigned char minutes;

    void normalize();

public:
    Time();
    Time(unsigned char hours, unsigned char minutes);
    Time(unsigned int totalMinutes);

    unsigned char getHours() const;
    unsigned char getMinutes() const;
    void setHours(unsigned char hours);
    void setMinutes(unsigned char minutes);

    Time addMinutes(unsigned int minutes) const;
    Time addTime(const Time& other) const;
    Time subtractTime(const Time& other) const;
    Time subtractMinutes(unsigned int minutes) const;

    Time& operator++();
    Time operator++(int);
    Time& operator--();
    Time operator--(int);

    explicit operator short int() const;
    operator bool() const;

    Time operator+(const Time& other) const;
    Time operator+(unsigned int minutes) const;
    Time operator-(const Time& other) const;
    Time operator-(unsigned int minutes) const;

    friend std::ostream& operator<<(std::ostream& out, const Time& time);

    unsigned int toTotalMinutes() const;
    std::string toString() const;
};