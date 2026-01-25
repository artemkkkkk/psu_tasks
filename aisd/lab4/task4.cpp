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

    int countMultiples = 0;
    for (int i = 0; i < N; ++i) {
        if (arr[i] % 3 == 0) {
            countMultiples++;
        }
    }

    if (countMultiples == 0) {
        cout << "Нет элементов, кратных 3. Массив без изменений:" << endl;
        for (int i = 0; i < N; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
        delete[] arr;
        return 0;
    }

    int* newArr = new int[N + countMultiples];
    int writeIndex = 0;

    for (int i = 0; i < N; ++i) {
        if (arr[i] % 3 == 0) {
            newArr[writeIndex++] = -1;
        }
        newArr[writeIndex++] = arr[i];
    }

    cout << "Массив после вставки -1 перед каждым элементом, кратным 3:" << endl;
    for (int i = 0; i < N + countMultiples; ++i) {
        cout << newArr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    delete[] newArr;
    return 0;
}