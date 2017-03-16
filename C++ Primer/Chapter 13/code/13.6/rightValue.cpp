#include <iostream>

void func(int&& x) {
    std::cout << &x << std::endl;
}

int main() {
    int a = 0;
    func(std::move(a));
    std::cout << &a << std::endl;
    func(5);
    return 0;
}
