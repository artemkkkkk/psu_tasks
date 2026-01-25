#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Введите размер массива N: ";
    cin >> N;

    int* arr = new int[N];
    cout << "Введите элементы массива: ";
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    int K1, K2;
    cout << "Введите K1 и K2 (K1 < K2): ";
    cin >> K1 >> K2;

    if (K2 <= K1) {
        cout << "K2 должно быть больше, чем K1";
    }

    int writeIndex = 0;
    for (int readIndex = 0; readIndex < N; ++readIndex) {
        if (!(arr[readIndex] < K2 && arr[readIndex] > K1)) {
            arr[writeIndex++] = arr[readIndex];
        }
    }

    cout << "Элементы, оставшиеся после удаления (в исходном порядке): ";
    for (int i = 0; i < writeIndex; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    return 0;
}