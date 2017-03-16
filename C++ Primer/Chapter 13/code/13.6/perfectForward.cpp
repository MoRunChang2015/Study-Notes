#include <iostream>

class A {
    public:
    int a = 0;
    A() = default;
    A(const A& t) {
        std::cout << "in the copy constructor" << std::endl;
        a = t.a;
    }
    A(A&& t) {
        std::cout << "in the move constructor" << std::endl;
        a = t.a;
    }
};

template<typename T>
void func(T t) {
    std::cout << "in func" << std::endl;
}

template<typename T>
void relay(T&& t) {
    std::cout << "in relay" << std::endl;
    func(std::forward<T>(t));
}

int main() {
    A a;
    relay(std::move(a));
    return 0;
}
