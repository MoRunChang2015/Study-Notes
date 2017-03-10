#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int count(int from, int to) {
    for (int i = from; i != to; ++i) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "finish" << std::endl;
    return to - from;
}

void print(std::future<int>& f) { std::cout << f.get() << std::endl; }

int main() {
    std::packaged_task<int(int, int)> task(count);
    std::future<int> f = task.get_future();

    std::thread t1(std::move(task), 1, 10);
    std::thread t2(print, std::ref(f));

    t1.join();
    t2.join();

    std::packaged_task<int(int, int)> task2;
    std::cout << task2.valid() << std::endl;
    return 0;
}
