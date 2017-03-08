#include <iostream>
#include <string>
#include <thread>

using namespace std;

class callable {
    string hello = "hello world!";

   public:
    void operator()() { cout << hello << endl; }
};

int main() {
    std::thread t{callable()};
    t.join();
    return 0;
}
