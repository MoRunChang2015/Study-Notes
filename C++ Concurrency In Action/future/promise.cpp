#include <iostream>
#include <thread>
#include <future>

void print(std::future<int>& f) {
    int x = f.get();
    std::cout << x << std::endl;
}

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread t(print, std::ref(f));
    p.set_value(10);
    t.join();
    return 0;
}
