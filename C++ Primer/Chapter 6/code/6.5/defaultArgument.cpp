#include "defaultArgument.hpp"
#include <iostream>
using namespace std;

void func(int a, double b, char c) {
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
}

void function(int a, char c) {
    cout << "a = " << a << endl;
    cout << "c = " << c << endl;
}

int main() {
    func();
    func(2);
    func(2, 1.0);
    func(2, 1.0, '#');
    function();
    return 0;
}
