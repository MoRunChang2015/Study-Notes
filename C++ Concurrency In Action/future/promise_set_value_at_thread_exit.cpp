#include <iostream>
#include <future>
#include <thread>
#include <chrono>

void set_pro(std::promise<int>& p) {
    p.set_value_at_thread_exit(10);
    std::cout << "sleep 5 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void get_fut(std::future<int>& f) {
    std::cout << f.get() << std::endl;
}


int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread t1(set_pro, std::ref(p));
    std::thread t2(get_fut, std::ref(f));
    t1.join();
    t2.join();
    return 0;
}
