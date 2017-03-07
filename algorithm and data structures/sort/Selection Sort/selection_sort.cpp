#include <iostream>

using namespace std;

void selection_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = 0;
        int pos = -1;
        for (int j = i; j < n; j++) {
            if (pos == -1 || min > a[j]) {
                pos = j;
                min = a[j];
            }
        }
        swap(a[i], a[pos]);
    }
}

int main() {
    int a[10] = {5, 9, 7, 8, 10, 11, 60, -5, 6, 0};
    selection_sort(a, 10);
    for (auto& x : a) cout << x << " ";
    cout << endl;
    return 0;
}
