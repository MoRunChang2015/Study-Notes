#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>

class A {
    friend void swap(A&, A&);
    int a;
    std::mutex m;
};

void swap(A& lhs, A& rhs) {
    if (&lhs == &rhs)
        return;
    std::lock(lhs.m, rhs.m);
    std::lock_guard<std::mutex> lock_l(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_r(rhs.m, std::adopt_lock);
    std::swap(lhs.a, rhs.a);
}

int main() {
    return 0;
}
