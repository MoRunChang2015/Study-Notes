#include <iostream>

class A {
   public:
    using size_a = int;

   private:
    size_a size;
};

int main() {
    A::size_a size_temp;
    return 0;
}
