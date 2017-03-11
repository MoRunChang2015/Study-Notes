#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<bool> ready(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;

void count(int id) {
    while (!ready) {
        std::this_thread::yield();
    }
    for (int i = 0; i < 100000000; ++i)
        ;

    if (!winner.test_and_set())
        std::cout << "thread No." + std::to_string(id) << " won!" << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count to 1 million..." << std::endl;
    for (int i = 0; i < 10; ++i) threads.push_back(std::thread(count, i));

    ready = true;

    for (auto& t : threads) t.join();
    return 0;
}
