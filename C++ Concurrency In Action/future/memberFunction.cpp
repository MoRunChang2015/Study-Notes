#include <future>
#include <iostream>
#include <thread>

struct A {
    int a = 0;
    int add(int t) { return a = a + t; }
};

int main() {
    A a;
    std::packaged_task<int(int)> task(
        std::bind(&A::add, &a, std::placeholders::_1));
    std::future<int> f = task.get_future();
    //std::thread t(std::move(task), 5);
    task(5);
    std::cout << f.get() << std::endl;
    std::cout << a.a << std::endl;
    //t.join();
    task.reset();
    f = task.get_future();
    std::thread t1(std::move(task), 5);
    std::cout << f.get() << std::endl;
    std::cout << a.a << std::endl;
    t1.join();
    return 0;
}
