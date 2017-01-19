#include <iostream>
using namespace std;
int a = 1;
int main() {
    cout << a << endl;
    int a = 2;
    cout << a << endl;
    cout << ::a << endl;
    return 0;
}
