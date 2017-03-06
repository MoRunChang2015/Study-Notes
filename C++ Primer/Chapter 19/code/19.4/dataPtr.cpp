#include <iostream>
using namespace std;

class A {
   public:
    static const int A::*data() { return &A::a; };

   private:
    int a = 123;
};

int main() {
    A temp;
    auto p = A::data();
    // auto p2 = &A::a;
    cout << temp.*p << endl;
    // cout << temp.*p2 << endl;
    return 0;
}
