#include <iostream>

using namespace std;

void bubble_sort(int a[], int n) {
    int pos, i = 0;
    while (i < n - 1) {
        pos = -1;
        for (int j = n - 1; j > i; j--)
            if (a[j] < a[j - 1]) {
                pos = j;
                swap(a[j], a[j - 1]);
            }
        if (pos == -1) break;
        i = pos;
    }
}

int main() {
    int a[10] = {5, 9, 7, 8, 10, 11, 60, -5, 6, 0};
    bubble_sort(a, 10);
    for (auto& x : a) cout << x << " ";
    cout << endl;
    return 0;
}
