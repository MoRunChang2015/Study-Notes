#include <iostream>
#include <condition_variable>
#include <thread>

int value;
std::condition_variable cv;

void read() {
    std::cin >> value;
    cv.notify_one();
}

int main() {
    std::cout << "Please, enter an integer (I'll be printing dots): \n";
    std::thread t(read);

    std::mutex m;
    std::unique_lock<std::mutex> lck(m);
    while (cv.wait_for(lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
        std::cout << '.' << std::flush;
    }

    std::cout << "You entered: " << value << std::endl;
    t.join();
    return 0;
}
