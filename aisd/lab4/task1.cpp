#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Введите размер массива N: ";
    cin >> N;

    if (N <= 0) {
        cout << "Ошибка: размер массива должен быть положительным." << endl;
        return 1;
    }

    int* X = new int[N];
    cout << "Введите элементы массива: ";
    for (int i = 0; i < N; ++i) {
        cin >> X[i];
    }

    int maxIndex = 0;
    for (int i = 1; i < N; ++i) {
        if (X[i] > X[maxIndex]) {
            maxIndex = i;
        }
    }

    if (maxIndex == N - 1) {
        cout << "Максимальный элемент — последний. Элементов после него нет." << endl;
        cout << "Сумма: 0" << endl;
        cout << "Произведение: 1" << endl;
    } else {
        long long sum = 0;
        long long product = 1;
        bool hasElements = false;

        for (int i = maxIndex + 1; i < N; ++i) {
            sum += X[i];
            product *= X[i];
            hasElements = true;
        }

        if (!hasElements) {
            sum = 0;
            product = 1;
        }

        cout << "Сумма элементов после максимального: " << sum << endl;
        cout << "Произведение элементов после максимального: " << product << endl;
    }

    delete[] X;
    return 0;
}