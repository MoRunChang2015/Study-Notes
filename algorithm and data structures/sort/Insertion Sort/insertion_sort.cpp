#include <iostream>

using namespace std;

void insert_sort(int a[], int n) {
    for (int i = 1; i < n; i++)
        if (a[i - 1] > a[i]) {
            int j = i - 1;
            int temp = a[i];
            while (temp < a[j] && j >= 0) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = temp;
        }
}

int main() {
    int a[10] = {5, 9, 7, 8, 10, 11, 60, -5, 6, 0};
    insert_sort(a, 10);
    for (auto& x : a) cout << x << " ";
    cout << endl;
    return 0;
}
