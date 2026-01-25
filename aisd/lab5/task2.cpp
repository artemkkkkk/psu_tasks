#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main() {
    int N;
    cout << "Введите размер массива N (N >= 20): ";
    cin >> N;

    if (N < 20) {
        cout << "Размер массива должен быть не менее 20!" << endl;
        return 0;
    }

    vector<int> arr(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-50, 50);

    for (int i = 0; i < N; ++i) {
        arr[i] = dis(gen);
    }

    cout << "Исходный массив: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n\n";

    vector<int> positives, negatives;

    for (int x : arr) {
        if (x > 0) positives.push_back(x);
        else if (x < 0) negatives.push_back(x);
    }

    sort(positives.begin(), positives.end());
    sort(negatives.begin(), negatives.end(), greater<int>());

    int pos_idx = 0, neg_idx = 0;
    vector<int> result = arr;

    for (int i = 0; i < N; ++i) {
        if (arr[i] > 0) {
            result[i] = positives[pos_idx++];
        } else if (arr[i] < 0) {
            result[i] = negatives[neg_idx++];
        }
    }

    cout << "Отсортированный массив: ";
    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}