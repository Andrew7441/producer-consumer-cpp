#include "producer_consumer.h"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>

static std::queue<int> buffer;
static std::mutex mtx;
static const unsigned int MAX_BUFFER_SIZE = 10u;
static std::condition_variable cond_var;

void produce_one(int value) {
    std::unique_lock<std::mutex> lock(mtx);
    cond_var.wait(lock, []() { return buffer.size() < MAX_BUFFER_SIZE; });

    buffer.push(value);

    std::cout << "Producing: " << value << std::endl;
    std::cout << "Buffer Size: " << buffer.size() << std::endl;

    lock.unlock();
    cond_var.notify_one();

}

void consume_one() {
    std::unique_lock<std::mutex> lock(mtx);
    cond_var.wait(lock, []() { return !buffer.empty(); });

    int value = buffer.front();
    buffer.pop();

    std::cout << "Consuming: " << value << std::endl;
    std::cout << "Buffer Size: " << buffer.size() << std::endl;

    lock.unlock();
    cond_var.notify_one();
    
}

void reset_buffer() {
    while (!buffer.empty()) buffer.pop();
}

bool buffer_empty() {
    return buffer.empty();
}

std::size_t buffer_size() {
    std::lock_guard<std::mutex> lock(mtx);
    return buffer.size();
}
