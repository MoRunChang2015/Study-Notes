#include <iostream>

using namespace std;

void selection_sort(int a[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int min = 0;
        int pos_min = -1;
        int max = 0;
        int pos_max = -1;
        for (int j = i; j < n - i; j++) {
            if (pos_min == -1 || min > a[j]) {
                pos_min = j;
                min = a[j];
            }
            if (pos_max == -1 || max < a[j]) {
                pos_max = j;
                max = a[j];
            }
        }
        swap(a[i], a[pos_min]);
        swap(a[n - i - 1], a[pos_max]);
    }
}

int main() {
    int a[11] = {5, 9, 7, 8, 10, 11, 60, -5, 6, 0, -77};
    selection_sort(a, 11);
    for (auto& x : a) cout << x << " ";
    cout << endl;
    return 0;
}
