#include <iostream>
#include <climits>

#ifdef _WIN32
    #include <io.h>
    #include <fcntl.h>
    #include <windows.h>
#endif


using namespace std;

void findMaxAndSum(int N, int& maxDigit, int& sumDigits) {
    maxDigit = INT_MIN;
    sumDigits = 0;

    while (N > 0) {
        int digit = N % 10;
        if (digit > maxDigit) {
            maxDigit = digit;
        }
        sumDigits += digit;
        N /= 10;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    int N;
    cout << "Введите натуральное число N: ";
    cin >> N;

    int maxDigit, sumDigits;
    findMaxAndSum(N, maxDigit, sumDigits);

    cout << "Максимальная цифра: " << maxDigit << endl;
    cout << "Сумма цифр: " << sumDigits << endl;

    return 0;
}