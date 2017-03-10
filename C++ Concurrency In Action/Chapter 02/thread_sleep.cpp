#include <iostream>
#include <thread>
#include <chrono>

void thread_task(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "Hello thread " << std::this_thread::get_id() << " paused " << n << " seconds" << std::endl;
}

int main() {
    std::thread threads[5];
    for (int i = 0; i < 5; i++) {
        threads[i] = std::thread(thread_task, i + 1);
    }
    for (auto &t : threads) {
        t.join();
    }
    return 0;
}
