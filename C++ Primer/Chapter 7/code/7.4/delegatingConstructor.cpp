#include <iostream>
using namespace std;

class A {
    public:
        A() : val(0) {
            cout << "finish A()" << endl;
        };
        A(int t):A() {
            val = t;
            cout << "finish A(int)" << endl;
        }
    private:
        int val;
};

int main() {
    A temp(0);
    return 0;
}
