#include "checker.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

void CheckFirstGraderHomework(const std::string& FN1, const std::string& FN2) {
    std::ifstream fin(FN1);
    std::ofstream fout(FN2);
    if (!fin || !fout) {
        throw std::runtime_error("Не удалось открыть файлы");
    }

    std::string line;
    while (std::getline(fin, line)) {
        // Удалим возможные пробелы
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty()) continue;

        size_t eq = line.find('=');
        if (eq == std::string::npos) {
            fout << line << " -\n";
            continue;
        }

        std::string expr = line.substr(0, eq);
        std::string ansStr = line.substr(eq + 1);

        // Найдём оператор
        size_t opPos = std::string::npos;
        char op = 0;
        if ((opPos = expr.find('+')) != std::string::npos) op = '+';
        else if ((opPos = expr.find('-')) != std::string::npos) op = '-';

        if (op == 0 || opPos == 0 || opPos == expr.size() - 1) {
            fout << line << " -\n";
            continue;
        }

        std::string aStr = expr.substr(0, opPos);
        std::string bStr = expr.substr(opPos + 1);

        if (aStr.size() != 1 || bStr.size() != 1 || !std::isdigit(aStr[0]) || !std::isdigit(bStr[0])) {
            fout << line << " -\n";
            continue;
        }

        int a = aStr[0] - '0';
        int b = bStr[0] - '0';
        int correct = (op == '+') ? a + b : a - b;

        try {
            int given = std::stoi(ansStr);
            fout << line << (given == correct ? " +" : " -") << "\n";
        } catch (...) {
            fout << line << " -\n";
        }
    }

    fin.close();
    fout.close();
}