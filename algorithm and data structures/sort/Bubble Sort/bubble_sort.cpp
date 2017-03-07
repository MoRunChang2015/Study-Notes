#include <iostream>

using namespace std;

void bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; j > i; j--)
            if (a[j] < a[j - 1]) swap(a[j], a[j - 1]);
}

int main() {
    int a[10] = {5, 9, 7, 8, 10, 11, 60, -5, 6, 0};
    bubble_sort(a, 10);
    for (auto& x : a) cout << x << " ";
    cout << endl;
    return 0;
}
