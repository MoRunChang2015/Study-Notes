#include <iostream>

using namespace std;

void merge_sort(int a[], int n) {
    if (n == 1)
        return;
    int mid = n / 2;
    merge_sort(a, mid);
    merge_sort(a + mid, n - mid);
    int *temp = new int[n + 1];
    int i = 0;
    int j = mid;
    int cnt = 0;
    while (i < mid || j < n) {
        if (i == mid) {
            temp[cnt] = a[j];
            ++j;
        } else if (j == n) {
            temp[cnt] = a[i];
            ++i;
        } else if (a[i] < a[j]) {
            temp[cnt] = a[i];
            ++i;
        } else {
            temp[cnt] = a[j];
            ++j;
        }
        ++cnt;
    }
    for (int i = 0; i < n; ++i)
        a[i] = temp[i];
    delete []temp;
}

int main() {
    int a[10] = {5, 9, 7, 8, 10, 11, 60, -5, 6, 0};
    merge_sort(a, 10);
    for (auto& x : a) cout << x << " ";
    cout << endl;
    return 0;
}
