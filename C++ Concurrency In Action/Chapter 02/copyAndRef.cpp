#include <iostream>
#include <thread>

using namespace std;

void func(int& a) {
    a++;
}

int main() {
    int a = 0, b = 0;
    //std::thread t(func, a); Error!
    //t.join();
    //cout << a << endl;

    std::thread t2(func, std::ref(b));
    t2.join();
    cout << b << endl;
    return 0;
}
