#include <iostream>

using namespace std;

int move(int a) {
    cout << "using move" << endl;
    return std::move(a);
}

int main() {
    int a = 0;
    int&& w = move(a);
    cout << w << endl;
    return 0;
}
