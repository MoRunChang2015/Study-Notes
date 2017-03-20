#include <iostream>
#include "shared_ptr.hpp"

class A {
   public:
    ~A() { std::cout << "in the A's destructor" << std::endl; }

    const int getValue() const { return a; }

    void setValue(int t) { a = t; }

   private:
    int a = 0;
};

int main() {
    shared_ptr<A> p(new A);
    (*p).setValue(10);
    std::cout << p->getValue() << std::endl;
    if (true) {
        shared_ptr<A> p1(std::move(p)), p2;
        p2 = p1;
    }
    std::cout << "outside" << std::endl;
    return 0;
}
