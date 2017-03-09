#include <iostream>
#include <thread>

using namespace std;

struct A {
    int a = 0;
    void add(int t) {
        a = a + t;
    }
};

int main() {
    A a;
    std::thread t(&A::add, a, 2);
    t.join();
    cout << a.a << endl;
    A b;
    std::thread t2(&A::add, &b, 2);
    t2.join();
    cout << b.a << endl;
    return 0;
}
