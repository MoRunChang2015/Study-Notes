#include<iostream>
using namespace std;
int main() {
    int a = 0;
    auto f = [a] ()mutable {a++; return a;};
    cout << f() << endl;
    cout << a << endl;
    return 0;
}
