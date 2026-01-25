#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Введите размер массива N (>3): ";
    cin >> N;

    if (N <= 3) {
        cout << "Ошибка: N должно быть больше 3." << endl;
        return 1;
    }

    int* arr = new int[N];
    cout << "Введите элементы массива: ";
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    int maxSum = arr[0] + arr[1] + arr[2];
    int startIdx = 0;

    for (int i = 1; i <= N - 3; ++i) {
        int currentSum = arr[i] + arr[i+1] + arr[i+2];
        if (currentSum > maxSum) {
            maxSum = currentSum;
            startIdx = i;
        }
    }

    cout << "Три последовательных элемента с максимальной суммой: "
         << arr[startIdx] << ", " << arr[startIdx+1] << ", " << arr[startIdx+2] << endl;
    cout << "Их сумма: " << maxSum << endl;

    delete[] arr;
    return 0;
}