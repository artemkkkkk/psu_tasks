#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>

class StackException : public std::runtime_error {
public:
    explicit StackException(const std::string& message)
        : std::runtime_error(message) {}
};

class ConversionException : public std::runtime_error {
public:
    explicit ConversionException(const std::string& message)
        : std::runtime_error(message) {}
};

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // EXCEPTIONS_H