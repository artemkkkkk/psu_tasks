#ifndef STRING_TASKS_H
#define STRING_TASKS_H

#include <string>
#include <vector>
#include <set>

// String41
int CountWords(const std::string& s);

// Str13
std::string ReplaceAngleBrackets(const std::string& s);

// Str22
struct CharTypeResult {
    bool isLetter;
    bool isDigit;
    bool isLower;
    bool isUpper;
    bool isControl;
};
CharTypeResult CheckCharType(char c);

// Str36
std::pair<int, std::string> CountUniqueNonPunctChars(const std::string& s);

// Str26
bool IsValidBinary(const std::string& s);
long long BinaryToDecimal(const std::string& s);

#endif // STRING_TASKS_H