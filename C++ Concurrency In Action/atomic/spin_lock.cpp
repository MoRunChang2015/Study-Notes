#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic_flag lock = ATOMIC_FLAG_INIT;

void f(int n) {
    for (int i = 0; i < 100; ++i) {
        while (lock.test_and_set(std::memory_order_acquire));
        std::cout << "Output from thread " << n << std::endl;
        lock.clear(std::memory_order_release);
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(f, i);
    }
    for (auto& i: threads) {
        i.join();
    }
    return 0;
}
