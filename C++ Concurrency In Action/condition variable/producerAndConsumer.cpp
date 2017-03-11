#include <condition_variable>
#include <ctime>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

std::mutex mtx;
std::condition_variable cv;

std::uniform_int_distribution<unsigned> u(0, 20);
std::default_random_engine e(time(0));

int cargo = 0;

bool check_cargo() { return !cargo == 0; }

void consumer(int id) {
    int random;
    while (true) {
        random = u(e);
        std::cout << "consumer " + std::to_string(id) + " sleep for " +
                         std::to_string(random) + " seconds"
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(random));

        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, check_cargo);
        --cargo;
        std::cout << "consumer " + std::to_string(id) +
                         " get one in cargo, cargo is "
                  << std::to_string(cargo) << " now." << std::endl;
        ;
    }
}

void producer(int id) {
    int random;
    while (true) {
        random = u(e);
        std::cout << "producer " + std::to_string(id) + " sleep for " +
                         std::to_string(random) + " seconds"
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(random));

        std::unique_lock<std::mutex> lck(mtx);
        ++cargo;
        std::cout << "producer " + std::to_string(id) +
                         " put one in cargo, cargo is "
                  << std::to_string(cargo) << " now." << std::endl;
        cv.notify_one();
    }
}

int main() {
    std::thread p[5];
    std::thread c[5];
    for (int i = 0; i < 5; i++) {
        p[i] = std::thread(producer, i);
        c[i] = std::thread(consumer, i);
    }

    for (int i = 0; i < 5; i++) {
        p[i].join();
        c[i].join();
    }
    return 0;
}
