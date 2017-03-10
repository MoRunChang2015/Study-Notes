#include <future>
#include <iostream>
#include <thread>
#include <chrono>

bool is_prime(int x) {
    for (int i = 2; i < x; ++i) {
        if (x % i == 0) return false;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return true;
}

int main() {
    //std::packaged_task<bool(int)> task(is_prime);
    std::future<bool> f = std::async(std::launch::async, is_prime, 444444443);
    //std::future<bool> f = task.get_future();
    //std::thread t(std::move(task), 444444443);

    std::cout << "checking.." << std::endl;
    std::chrono::milliseconds span(100);
    while (f.wait_for(span) == std::future_status::timeout) {
        std::cout << "." << std::flush;
    }
    bool x = f.get();
    std::cout << std::endl
              << "444444443" << (x ? " is " : " is not ") << " prime." << std::endl;
    //t.join();
    return 0;
}
