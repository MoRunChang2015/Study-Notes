#include <iostream>
#include <future>
#include <thread>
#include <chrono>

void print(char c, int ms) {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        std::cout << c << std::flush;
    }
}

int main() {
    std::future<void> foo = std::async(std::launch::async, print, '*', 100);
    std::future<void> bar = std::async(std::launch::async, print, '@', 200);
    foo.get();
    bar.get();
    std::cout << std::endl;

    foo = std::async(std::launch::deferred, print, '*', 100);
    bar = std::async(std::launch::deferred, print, '@', 200);

    foo.get();
    bar.get();
    std::cout << std::endl;
    return 0;
}
