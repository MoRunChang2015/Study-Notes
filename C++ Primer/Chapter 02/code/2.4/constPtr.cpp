#include <iostream>
using namespace std;

int main() {
    int a = 0, b = 5;
    const int *p1 = &a;
    p1 = &b;

    int const *p2 = &a;
    p2 = &b;

    int *const p3 = &a;
    *p3 = 100;

    int const *const p4 = &a;
    return 0;
}
