#include <unordered_set>
#include <iostream>
#include <string>

using namespace std;

struct A {
    int a;
    string s;
};

size_t hasher(const A& a) {
    return hash<string>()(a.s);
}

bool eqOp(const A& a, const A& b) {
    return a.a == b.a;
}

int main() {
    unordered_set<A, decltype(hasher)*, decltype(eqOp)*> a(42, hasher, eqOp);
    return 0;
}
