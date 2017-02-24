#include <iostream>
using namespace std;

constexpr int func(int a) {
    return (a == 1 || a == 2) ? 1 : func(a - 1) + func(a - 2);
}

int main() {
    cout << func(5) << endl;
    int a[func(5)];
    return 0;
}
