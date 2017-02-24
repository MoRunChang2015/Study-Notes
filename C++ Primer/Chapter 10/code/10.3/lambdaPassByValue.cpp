#include <iostream>
using namespace std;
int main() {
    int v = 42;
    auto f = [&v] {return v++;};
    v = 0;
    cout << f() << endl;
    return 0;
}
