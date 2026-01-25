#include <iostream>

using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");

    int N;
    cout << "Введите N: ";
    cin >> N;

    if (N < 0) {
        cout << "N должно быть >= 0" << endl;
        return 0;
    }

    long long result = 0;

    if (N == 0) {
        result = 1;
    }
    else if (N == 1) {
        result = 1;
    }
    else if (N == 2) {
        result = 2;
    }
    else {
        long long a = 1;
        long long b = 1;
        long long c = 2;

        for (int i = 3; i <= N; ++i) {
            result = a + b + c;

            a = b;
            b = c;
            c = result;
        }
    }

    cout << "Количество путей: " << result << endl;

    return 0;
}