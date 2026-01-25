#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    int N;
    cout << "Введите N (0 < N < 60): ";
    cin >> N;

    if (N <= 0) return 0;
    if (N >= 60) return 0;

    double safe_count = 0;
    
    if (N == 1) {
        safe_count = 2;
    }
    else if (N == 2) {
        safe_count = 4;
    }
    else if (N == 3) {
        safe_count = 8;
    }
    else {
        double p4 = 1;
        double p3 = 2;
        double p2 = 4;
        double p1 = 8;

        for (int i = 4; i <= N; ++i) {
            safe_count = p1 + p2 + p3 + p4;

            p4 = p3;
            p3 = p2;
            p2 = p1;
            p1 = safe_count;
        }
    }

    double total = pow(2.0, N);
    
    double result = total - safe_count;

    cout << fixed << setprecision(0);
    cout << "Взрывоопасных стопок: " << result << endl;

    return 0;
}