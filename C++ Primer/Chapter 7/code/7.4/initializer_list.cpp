#include <iostream>
using namespace std;

class A {
    public:
        A(const int t_a, int t_b, int& t_c) : a(t_a), b(t_b), c(t_c) {};
    private:
        const int a;
        int b;
        int& c;
};

int main() {
    int temp = 0;
    A t_a(5, 3, temp);
    return 0;
}
