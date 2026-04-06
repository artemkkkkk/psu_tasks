#include "recur14.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

int parseTerm(const string& s, int& pos) {
    if (pos >= s.length()) throw runtime_error("Expected digit");
    if (!isdigit(s[pos])) throw runtime_error(string("Invalid character: ") + s[pos]);

    int val = s[pos] - '0';
    pos++;
    return val;
}

int parseRest(const string& s, int& pos, int currentVal) {
    if (pos >= s.length()) {
        return currentVal;
    }

    char op = s[pos];
    if (op != '+' && op != '-') {
        return currentVal;
    }

    pos++;

    int nextTerm = parseTerm(s, pos);

    int newVal = (op == '+') ? (currentVal + nextTerm) : (currentVal - nextTerm);

    return parseRest(s, pos, newVal);
}

int evaluate(const string& s) {
    if (s.empty()) throw runtime_error("Empty expression");
    int pos = 0;
    int firstTerm = parseTerm(s, pos);
    return parseRest(s, pos, firstTerm);
}

void solveRecur14() {
    cout << "\n--- Запуск задачи Recur14 ---" << endl;
    cout << "Введите выражение (например, 1+2-3+4): ";

    string expression;
    cin >> expression;

    try {
        int result = evaluate(expression);

        ofstream fout("output.txt");
        if (fout.is_open()) {
            fout << result << endl;
            fout.close();
            cout << "Результат записан в output.txt: " << result << endl;
        } else {
            cerr << "Ошибка записи в output.txt" << endl;
        }
    } catch (const exception& e) {
        cerr << "Ошибка вычисления: " << e.what() << endl;
    }
}