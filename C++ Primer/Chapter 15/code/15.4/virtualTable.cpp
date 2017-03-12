#include <iostream>

class Base1 {
    private:
        int a;
    public:
        virtual void func() {
            std::cout << "Base 1" << std::endl;
        }
};

class Base2 {
    private:
        int a;
    public:
        virtual void func() {
            std::cout << "Base 2" << std::endl;
        }
};

class Derived : public Base1, public Base2 {
    public:
        void func() override {
            std::cout << "Derived" << std::endl;
        }
};


int main() {
    std::cout << sizeof(Base1) << std::endl;
    std::cout << sizeof(Base2) << std::endl;
    std::cout << sizeof(Derived) << std::endl;
    Derived d;
    Base1& b1 = d;
    Base2& b2 = d;
    b1.func();
    b2.func();
    return 0;
}
