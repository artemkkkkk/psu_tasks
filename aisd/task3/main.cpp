#include <iostream>

#ifdef _WIN32
    #include <io.h>
    #include <fcntl.h>
    #include <windows.h>
#endif

using namespace std;

long long factorial(int n) {
    if (n <= 1) return 1;
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

long long computeSum(int N) {
    long long sum = 0;
    for (int i = 1; i <= N; i++) {
        sum += factorial(i);
    }
    return sum;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    int N;
    cout << "Введите натуральное число N (N < 15): ";
    cin >> N;

    if (N >= 15) {
        cout << "Ошибка: N должно быть меньше 15!" << endl;
        return 1;
    }

    long long S = computeSum(N);
    cout << "Сумма S = " << S << endl;

    return 0;
}