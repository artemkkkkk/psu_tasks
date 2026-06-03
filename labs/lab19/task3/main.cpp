#include <iostream>
#include <string>
#include <cctype>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

string vigenereEncrypt(const string& text, const string& key) {
    string result = "";
    int keyLen = key.length();
    int keyIdx = 0;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int shift = toupper(key[keyIdx % keyLen]) - 'A';
            char encrypted = (c - base + shift) % 26 + base;
            result += encrypted;
            keyIdx++;
        } else {
            result += c;
        }
    }
    return result;
}

string vigenereDecrypt(const string& text, const string& key) {
    string result = "";
    int keyLen = key.length();
    int keyIdx = 0;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int shift = toupper(key[keyIdx % keyLen]) - 'A';
            char decrypted = (c - base - shift + 26) % 26 + base;
            result += decrypted;
            keyIdx++;
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    string text = "London is the capital of great britain";
    string key = "envelope";

    cout << "Исходный текст : " << text << endl;
    cout << "Ключ         : " << key << endl;

    string encrypted = vigenereEncrypt(text, key);
    cout << "Зашифрованный: " << encrypted << endl;

    string decrypted = vigenereDecrypt(encrypted, key);
    cout << "Расшифрованный: " << decrypted << endl;

    if (text == decrypted) {
        cout << "\n[УСПЕХ] Дешифрованный текст совпадает с исходным." << endl;
    } else {
        cout << "\n[ОШИБКА] Тексты не совпадают!" << endl;
    }

    return 0;
}