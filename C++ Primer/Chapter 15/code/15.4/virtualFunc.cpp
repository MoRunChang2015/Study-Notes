#include <iostream>
using namespace std;

class Base {
    public:
        virtual void func() { cout << "Base!" << endl; }
};

class Derived : public Base {
    public:
        void func() override { cout << "Derived!" << endl; }
};

class Derived2: public Base {
    public:
        void func_test(int) {cout << "Derived!" << endl;}
};

int main() {
    Base b;
    Derived d;
    Derived2 d2;
    Base& br = d;
    br.func();
    Base& br2 = b;
    Base& br3 = d2;
    br2.func();
    br3.func();
    return 0;
}
