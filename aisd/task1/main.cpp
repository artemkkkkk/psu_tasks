#include <iostream>
#include <string>
#include <cmath>

#ifdef _WIN32
    #include <io.h>
    #include <fcntl.h>
    #include <windows.h>
#endif


using namespace std;

int binaryToDecimal(string binary) {
    int decimal = 0;
    int power = 0;

    // Обходим строку справа налево (от младшего разряда к старшему)
    for (int i = binary.length() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += pow(2, power);
        }
        power++;
    }

    return decimal;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    string N2;
    cout << "Введите двоичное число: ";
    cin >> N2;

    int result = binaryToDecimal(N2);
    cout << "Десятичное представление: " << result << endl;

    return 0;
}