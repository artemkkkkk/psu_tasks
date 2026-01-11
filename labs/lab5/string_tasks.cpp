#include "string_tasks.h"
#include <cctype>
#include <algorithm>
#include <sstream>

// String41
int CountWords(const std::string& s) {
    if (s.empty()) return 0;
    std::istringstream iss(s);
    std::string word;
    int count = 0;
    while (iss >> word) ++count;
    return count;
}

// Str13
std::string ReplaceAngleBrackets(const std::string& s) {
    std::string res;
    for (char c : s) {
        if (c == '<') res += "begin";
        else if (c == '>') res += "end";
        else res += c;
    }
    return res;
}

// Str22
CharTypeResult CheckCharType(char c) {
    CharTypeResult r{};
    unsigned char uc = static_cast<unsigned char>(c);
    r.isLetter = std::isalpha(uc) != 0;
    r.isDigit = std::isdigit(uc) != 0;
    r.isLower = std::islower(uc) != 0;
    r.isUpper = std::isupper(uc) != 0;
    r.isControl = (uc >= 0 && uc <= 32);
    return r;
}

// Str36
bool isPunctuation(char c) {
    return std::ispunct(static_cast<unsigned char>(c)) != 0;
}

std::pair<int, std::string> CountUniqueNonPunctChars(const std::string& s) {
    std::set<char> unique;
    for (char c : s) {
        if (!isPunctuation(c)) {
            unique.insert(c);
        }
    }
    std::string chars(unique.begin(), unique.end());
    return {static_cast<int>(unique.size()), chars};
}

// Str26
bool IsValidBinary(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s)
        if (c != '0' && c != '1')
            return false;
    return true;
}

long long BinaryToDecimal(const std::string& s) {
    long long res = 0;
    for (char c : s) {
        res = res * 2 + (c - '0');
    }
    return res;
}