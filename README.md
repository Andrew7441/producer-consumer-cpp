# Producer-Consumer C++

A small C++ multithreading project that demonstrates the classic **Producer-Consumer problem** using a shared bounded buffer.

The project shows how one thread can safely produce data while another thread consumes it without race conditions.

---

## Problem It Solves

When multiple threads access the same shared data, they can interfere with each other.

This project solves that by making sure:

- The producer waits if the buffer is full.
- The consumer waits if the buffer is empty.
- Only one thread accesses the buffer at a time.

This is handled using:

- `std::mutex`
- `std::unique_lock`
- `std::condition_variable`
- `std::queue`

---

## How It Works

The producer adds integers to a shared queue.

The consumer removes integers from that queue.

The buffer has a maximum size, so the producer cannot add forever. If the buffer is full, the producer waits. If the buffer is empty, the consumer waits.

Basic flow:

```text
Producer Thread -> Shared Buffer -> Consumer Thread
```
## Project Structure

include/
  producer_consumer.h      # Function declarations

src/
  producer_consumer.cpp    # Shared buffer and synchronization logic
  main.cpp                 # Runs the demo scenarios

tests/
  test_main.cpp            # Unit tests

## Scenarios

- Buffer Full

The producer starts first and fills the buffer.

This demonstrates what happens when the producer is faster than the consumer.

- Buffer Not Full

The producer and consumer run at a similar speed.

This demonstrates normal producer-consumer behavior where the buffer does not fill up.

## Build and Run

From the project root:
```txt
cmake -S . -B build
cmake --build build
./build/producer_consumer
```
Then choose:
full
or:
not-full

## Run Tests

cd build
ctest

## Key Concepts

Mutex

A mutex protects the shared buffer so only one thread can use it at a time.

Condition Variable

A condition variable lets a thread sleep until a condition becomes true.

In this project:

Producer waits until the buffer is not full.
Consumer waits until the buffer is not empty.
Producer-Consumer Pattern

This pattern is used in real systems like task queues, job processors, and thread pools.

A producer adds work to a queue, and a consumer removes and processes that work.