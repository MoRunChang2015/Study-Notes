#include <iostream>
#include <map>

using namespace std;

struct A {
    int a, b;
};

bool cmp(const A& a, const A& b) {
    return a.a < b.a;
}

int main() {
    map<A, int, decltype(cmp)*> a(cmp);
    return 0;
}
