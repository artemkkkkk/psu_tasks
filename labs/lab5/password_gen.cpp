#include "password_gen.h"
#include <random>
#include <string>
#include <ctime>
#include <stdexcept>

std::string GeneratePassword(int level) {
    static std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));

    std::string chars;
    int length = 0;

    switch (level) {
        case 1:
            chars = "abcdefghijklmnopqrstuvwxyz";
            length = 8;
            break;
        case 2:
            chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            length = 12;
            break;
        case 3:
            chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";
            length = 16;
            break;
        default:
            throw std::invalid_argument("Уровень должен быть 1, 2 или 3");
    }

    std::uniform_int_distribution<> dis(0, static_cast<int>(chars.size()) - 1);
    std::string pwd;
    for (int i = 0; i < length; ++i)
        pwd += chars[dis(gen)];
    return pwd;
}
