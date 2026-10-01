#include "time.h"
#include <iostream>
#include <cstdio>

unsigned Time::normalize(unsigned total) {
    return total % (24u * 60u);
}

unsigned Time::totalMinutes() const {
    return static_cast<unsigned>(hours) * 60u + static_cast<unsigned>(minutes);
}

void Time::setTotal(unsigned total) {
    unsigned norm = normalize(total);
    hours = static_cast<unsigned char>(norm / 60u);
    minutes = static_cast<unsigned char>(norm % 60u);
}

Time::Time() : hours(0), minutes(0) {}

Time::Time(unsigned char h, unsigned char m) {
    setTotal(static_cast<unsigned>(h) * 60u + static_cast<unsigned>(m));
}

Time::Time(unsigned totalMinutes) {
    setTotal(totalMinutes);
}

unsigned char Time::getHours() const {
    return hours;
}

unsigned char Time::getMinutes() const {
    return minutes;
}

Time Time::addMinutes(unsigned m) const {
    return Time(totalMinutes() + m);
}

Time& Time::operator++() {
    setTotal(totalMinutes() + 1u);
    return *this;
}

Time Time::operator++(int) {
    Time old = *this;
    ++(*this);
    return old;
}

Time& Time::operator--() {
    setTotal(totalMinutes() + 24u * 60u - 1u);
    return *this;
}

Time Time::operator--(int) {
    Time old = *this;
    --(*this);
    return old;
}

Time::operator short int() const {
    return static_cast<short>(hours);
}

Time::operator bool() const {
    return hours != 0 || minutes != 0;
}

Time Time::operator+(unsigned m) const {
    return addMinutes(m);
}

Time Time::operator-(unsigned m) const {
    unsigned sub = m % (24u * 60u);
    return Time((totalMinutes() + 24u * 60u - sub) % (24u * 60u));
}

std::ostream& operator<<(std::ostream& out, const Time& t) {
    char buffer[8];
    std::snprintf(
        buffer,
        8,
        "%02u:%02u",
        static_cast<unsigned>(t.hours),
        static_cast<unsigned>(t.minutes)
    );

    return out << buffer;
}