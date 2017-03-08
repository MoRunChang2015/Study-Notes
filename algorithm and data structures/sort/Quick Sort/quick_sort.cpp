#include <iostream>

using namespace std;

void quick_sort(int a[], int n) {
    int i = 0, j = n - 1;
    int mid = a[(i + j) / 2];
    while (i < j) {
        while (a[i] < mid) ++i;
        while (a[j] > mid) --j;
        if (i <= j) {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (j > 0) quick_sort(a, j + 1);
    if (i < n - 1) quick_sort(a + i, n - i);
}

int main() {
    int a[10] = {5, 9, 7, 8, 10, 11, 60, -5, 6, 0};
    quick_sort(a, 10);
    for (auto& x : a) cout << x << " ";
    cout << endl;
    return 0;
}
