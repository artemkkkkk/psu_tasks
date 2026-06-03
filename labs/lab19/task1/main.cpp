#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

string encodeHamming(const string& msg) {
    int m = msg.length();
    int r = 0;
    while ((1 << r) < m + r + 1) {
        r++;
    }

    int n = m + r;
    vector<char> hamming(n + 1, '0');

    int msgIdx = 0;
    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) != 0) {
            hamming[i] = msg[msgIdx++];
        }
    }

    for (int i = 0; i < r; i++) {
        int pos = 1 << i; // 1, 2, 4, 8...
        int parity = 0;
        for (int j = pos; j <= n; j++) {
            if ((j & pos) != 0) {
                parity ^= (hamming[j] - '0');
            }
        }
        hamming[pos] = parity + '0';
    }

    string result = "";
    for (int i = 1; i <= n; i++) {
        result += hamming[i];
    }
    return result;
}

string correctHamming(string encoded) {
    int n = encoded.length();
    vector<char> h(n + 1, '0');
    for (int i = 0; i < n; i++) {
        h[i + 1] = encoded[i];
    }

    int r = 0;
    while ((1 << r) < n + 1) r++;

    int errorPos = 0;
    for (int i = 0; i < r; i++) {
        int pos = 1 << i;
        int parity = 0;
        for (int j = pos; j <= n; j++) {
            if ((j & pos) != 0) {
                parity ^= (h[j] - '0');
            }
        }
        if (parity != 0) {
            errorPos += pos;
        }
    }

    if (errorPos > 0) {
        cout << "Обнаружена ошибка в позиции: " << errorPos << endl;
        h[errorPos] = (h[errorPos] == '0') ? '1' : '0';
        cout << "Ошибка исправлена." << endl;
    } else {
        cout << "Ошибок не обнаружено." << endl;
    }

    string corrected = "";
    for (int i = 1; i <= n; i++) {
        corrected += h[i];
    }
    return corrected;
}

string extractMessage(const string& hamming) {
    string msg = "";
    int n = hamming.length();
    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) != 0) {
            msg += hamming[i - 1];
        }
    }
    return msg;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    string originalMsg = "1011";
    cout << "Исходное сообщение: " << originalMsg << endl;

    string encoded = encodeHamming(originalMsg);
    cout << "Закодированное сообщение (Хемминг): " << encoded << endl;

    string corrupted = encoded;
    corrupted[2] = (corrupted[2] == '0') ? '1' : '0';
    cout << "Сообщение с ошибкой (бит 3 инвертирован): " << corrupted << endl;

    string corrected = correctHamming(corrupted);
    cout << "Исправленное сообщение: " << corrected << endl;

    string finalMsg = extractMessage(corrected);
    cout << "Извлеченное исходное сообщение: " << finalMsg << endl;

    return 0;
}