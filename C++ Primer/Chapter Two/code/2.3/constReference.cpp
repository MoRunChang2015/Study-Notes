#include <iostream>
using namespace std;

int main() {
    int a = 0;
    int& b = a;
    const int& c = a;
    b = 1;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;

    double pi = 3.14;
    // int& d = pi; Error
    const int& e = pi;
    return 0;
}
