#include <iostream>

using namespace std;

int quick_sort_kth(int a[], int n, int k) {
    if (n == 1)
        return a[0];
    int i = 0, j = n - 1;
    int mid = a[(i + j) / 2];
    while (i <= j) {
        while (a[i] < mid) ++i;
        while (a[j] > mid) --j;
        if (i <= j) {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i >= k && j + 1 < k)
        return mid;
    else if (j + 1 < k)
        return quick_sort_kth(a + i, n - i, k - i);
    else
        return quick_sort_kth(a, j + 1, k);
}

int main() {
    int a[10] = {5, 9, 7, 8, 10, 11, 60, 5, 6, 0};
    cout << quick_sort_kth(a, 10, 2);
    cout << endl;
    return 0;
}
