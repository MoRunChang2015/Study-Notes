#include <iostream>

using namespace std;

void heap_push(int a[], int x, int n) {
    int i = x;
    while (i < n) {
        int max = -1;
        int pos_max = -1;
        if (i * 2 + 1 < n && (pos_max == -1 || max < a[i * 2 + 1])) {
            pos_max = i * 2 + 1;
            max = a[i * 2 + 1];
        }
        if (i * 2 + 2 < n && (pos_max == -1 || max < a[i * 2 + 2])) {
            pos_max = i * 2 + 2;
            max = a[i * 2 + 2];
        }
        if (pos_max == -1 || max < a[i]) break;
        swap(a[i], a[pos_max]);
        i = pos_max;
    }
}

void heap_sort(int a[], int n) {
    for (int i = n / 2; i >= 0; i--) heap_push(a, i, n);
    for (int i = 0; i < n - 1; i++) {
        swap(a[0], a[n - i - 1]);
        heap_push(a, 0, n - i - 1);
    }
}

int main() {
    int a[10] = {5, 9, 7, 8, 10, 11, 60, -5, 6, 0};
    heap_sort(a, 10);
    for (auto& x : a) cout << x << " ";
    cout << endl;
    return 0;
}
