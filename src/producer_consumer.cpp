//Implements a shared buffer logic for the producer-consumer problem
//uses a mutex and a condition variable to safely produce and consume items

#include "producer_consumer.h"
#include <queue>                //queue for shared buffer
#include <mutex>                //used for locking
#include <condition_variable>   //used for thread waiting
#include <iostream>

static std::queue<int> buffer;                      //shared queue used as the buffer
static std::mutex mtx;                              //mutex protects acced to the shared buffer. used to make sure only one thread can access shared data
static const unsigned int MAX_BUFFER_SIZE = 10u;   
static std::condition_variable cond_var;            //used to block/wait producer and consumer threads

//produces one integer into the buffer
void produce_one(int value) {
    std::unique_lock<std::mutex> lock(mtx);                                    // locks the mutex so the thread has exclusive access to the buffer
    cond_var.wait(lock, []() { return buffer.size() < MAX_BUFFER_SIZE; });    // waits until buffer is not full

    buffer.push(value);// enqueue the value

    std::cout << "Producing: " << value << std::endl;
    std::cout << "Buffer Size: " << buffer.size() << std::endl;

    lock.unlock();              // unlocks before notifying anothe thread
    cond_var.notify_one();      // wakes one waiting producer/consumer
}

//consumes one integer from the buffer
void consume_one() {
    std::unique_lock<std::mutex> lock(mtx); //locks mutex before accessing the buffer
    cond_var.wait(lock, []() { return !buffer.empty(); }); // wait until buffer has data

    int value = buffer.front(); 
    buffer.pop();

    std::cout << "Consuming: " << value << std::endl;
    std::cout << "Buffer Size: " << buffer.size() << std::endl;

    lock.unlock();          //unlock before notifying another waiting thread
    cond_var.notify_one();  //wakes up a producer/consumer problem
}

//clears all items from the buffer
void reset_buffer() {
    while (!buffer.empty()) buffer.pop();
}
//checks whether buffer is empty
bool buffer_empty() {
    return buffer.empty();
}
//return current buffer size
std::size_t buffer_size() {
    std::lock_guard<std::mutex> lock(mtx); // lock before returning the size
    return buffer.size(); // returns the number of items in the buffer
}
