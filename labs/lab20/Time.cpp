#include "Time.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

Time::Time() : hours(0), minutes(0) {}

Time::Time(unsigned char hours, unsigned char minutes) {
    int total = static_cast<int>(hours) * 60 + static_cast<int>(minutes);
    while (total < 0) {
        total += 24 * 60;
    }
    total = total % (24 * 60);
    this->hours = total / 60;
    this->minutes = total % 60;
}

Time::Time(unsigned int totalMinutes) {
    totalMinutes = totalMinutes % (24 * 60);
    hours = totalMinutes / 60;
    minutes = totalMinutes % 60;
}

void Time::normalize() {
    int total = hours * 60 + minutes;
    while (total < 0) {
        total += 24 * 60;
    }
    total = total % (24 * 60);
    hours = total / 60;
    minutes = total % 60;
}

unsigned char Time::getHours() const {
    return hours;
}

unsigned char Time::getMinutes() const {
    return minutes;
}

void Time::setHours(unsigned char hours) {
    if (hours >= 24) {
        throw std::invalid_argument("Часы должны быть в диапазоне 0-23");
    }
    this->hours = hours;
}

void Time::setMinutes(unsigned char minutes) {
    if (minutes >= 60) {
        throw std::invalid_argument("Минуты должны быть в диапазоне 0-59");
    }
    this->minutes = minutes;
}

Time Time::addMinutes(unsigned int minutesToAdd) const {
    unsigned int total = toTotalMinutes() + minutesToAdd;
    return Time(total);
}

Time Time::addTime(const Time& other) const {
    unsigned int total = toTotalMinutes() + other.toTotalMinutes();
    return Time(total);
}

Time Time::subtractTime(const Time& other) const {
    int total = static_cast<int>(toTotalMinutes()) - static_cast<int>(other.toTotalMinutes());
    while (total < 0) {
        total += 24 * 60;
    }
    return Time(static_cast<unsigned int>(total));
}

Time Time::subtractMinutes(unsigned int minutesToSubtract) const {
    int total = static_cast<int>(toTotalMinutes()) - static_cast<int>(minutesToSubtract);
    while (total < 0) {
        total += 24 * 60;
    }
    return Time(static_cast<unsigned int>(total));
}

Time& Time::operator++() {
    minutes++;
    normalize();
    return *this;
}

Time Time::operator++(int) {
    Time temp = *this;
    ++(*this);
    return temp;
}

Time& Time::operator--() {
    int total = toTotalMinutes() - 1;
    if (total < 0) {
        total += 24 * 60;
    }
    hours = total / 60;
    minutes = total % 60;
    return *this;
}

Time Time::operator--(int) {
    Time temp = *this;
    --(*this);
    return temp;
}

Time::operator short int() const {
    return static_cast<short int>(hours);
}

Time::operator bool() const {
    return hours != 0 || minutes != 0;
}

Time Time::operator+(const Time& other) const {
    return addTime(other);
}

Time Time::operator+(unsigned int minutesToAdd) const {
    return addMinutes(minutesToAdd);
}

Time Time::operator-(const Time& other) const {
    return subtractTime(other);
}

Time Time::operator-(unsigned int minutesToSubtract) const {
    return subtractMinutes(minutesToSubtract);
}

std::ostream& operator<<(std::ostream& out, const Time& time) {
    out << std::setfill('0') << std::setw(2) << static_cast<int>(time.hours)
        << ":" << std::setfill('0') << std::setw(2) << static_cast<int>(time.minutes);
    return out;
}

unsigned int Time::toTotalMinutes() const {
    return hours * 60 + minutes;
}

std::string Time::toString() const {
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}