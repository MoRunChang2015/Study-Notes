#include <iostream>

using namespace std;

void insert_sort(int a[], int n, int d) {
    for (int i = d; i < n; i += d)
        if (a[i - d] > a[i]) {
            int j = i - d;
            int temp = a[i];
            while (temp < a[j] && j >= 0) {
                a[j + d] = a[j];
                j -= d;
            }
            a[j + d] = temp;
        }
}

void shell_sort(int a[], int n) {
    int d = n / 2;
    while (d >= 1) {
        insert_sort(a, n, d);
        d = d / 2;
    }
}

int main() {
    int a[10] = { 5, 9, 7, 8, 10, 11, 60, -5, 6, 0};
    shell_sort(a, 10);
    for (auto& x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
