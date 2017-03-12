#include <iostream>

class Base {
    long double a;
    virtual void func() = 0;
};

class Base1 :virtual public Base {
   private:
    int a;
   public:
    virtual void func() { std::cout << "Base 1" << std::endl; }
};

class Base2 : virtual public Base {
   private:
    int a;

   public:
    virtual void func() { std::cout << "Base 2" << std::endl; }
};

class Derived : public Base1, public Base2 {
   public:
    void func() override { std::cout << "Derived" << std::endl; }
};

int main() {
    std::cout << sizeof(Base) << std::endl;
    std::cout << sizeof(Base1) << std::endl;
    std::cout << sizeof(Base2) << std::endl;
    std::cout << sizeof(Derived) << std::endl;
    Base1 b1;
    Base2 b2;
    Derived d;
    return 0;
}
