#include <iostream>

using namespace std;

int main() {
    int a = 0;
    auto f = [=](auto x) mutable {
        a = a + x;
        cout << a << endl;
    };
    a = -1;
    f(5);
    cout << a << endl;
    return 0;
}
