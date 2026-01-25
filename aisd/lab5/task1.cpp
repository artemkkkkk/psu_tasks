// #include <iostream>
// #include <vector>
// #include <random>
//
// using namespace std;
//
// int main() {
//     int N;
//     cout << "Введите размер массива N: ";
//     cin >> N;
//
//     if (N <= 0) {
//         cout << "Размер массива должен быть положительным!" << endl;
//         return 1;
//     }
//
//     vector<int> arr(N);
//     random_device rd;
//     mt19937 gen(rd());
//     uniform_int_distribution<> dis(-100, 100);
//
//     for (int i = 0; i < N; ++i) {
//         arr[i] = dis(gen);
//     }
//
//     cout << "Исходный массив: ";
//     for (int x : arr) {
//         cout << x << " ";
//     }
//     cout << "\n\n";
//
//     for (int i = 0; i < N - 1; ++i) {
//         int min_index = i;
//         for (int j = i + 1; j < N; ++j) {
//             if (arr[j] < arr[min_index]) {
//                 min_index = j;
//             }
//         }
//
//         swap(arr[i], arr[min_index]);
//
//         cout << "Шаг " << (i + 1) << ": ";
//         for (int x : arr) {
//             cout << x << " ";
//         }
//         cout << endl;
//     }
//
//     cout << "\nОтсортированный массив: ";
//     for (int x : arr) {
//         cout << x << " ";
//     }
//     cout << endl;
//
//     return 0;
// }