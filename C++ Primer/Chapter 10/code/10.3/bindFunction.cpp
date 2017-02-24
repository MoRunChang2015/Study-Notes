#include <iostream>
#include <functional>
using namespace std;

void func(char c, int n) {
    for (int i = 0; i < n; i++)
        cout << c << " ";
    cout << endl;
}

int main() {
    int a = 5;
    auto temp = bind(func, placeholders::_1, a);
    temp('a');
    return 0;
}
