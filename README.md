## Table of Contents

* [Overview](#overview)
* [Prerequisites](#prerequisites)
* [Scenarios](#scenarios)
* [How to Run](#how-to-run)
* [Unit Tests](#Unit-tests)
* [Key Concepts](#key-concepts)

### Overview

The Producer-Consumer Problem is a classic concurrency problem where producers generate data and consumers retrieve it from a shared buffer. 

Synchronization ensures:

Producers wait if the buffer is full.

Consumers wait if the buffer is empty.

### Prerequisites

C++17 or later

Multithreading support (Linux, macOS, Windows)


### Scenarios

Buffer Not Full
- Producer and consumer operate at similar speed.
- Buffer never exceeds maximum size (10).

Buffer Full
- Producer starts first and fills the buffer.
- Consumer starts after a delay to demonstrate full-buffer behavior.

### How to run

g++ -std=c++17 producer_consumer.cpp -pthread -o producer_consumer
./producer_consumer

### Unit Tests
Unit tests verify the correctness of the buffer logic independently of threads.

Uses GoogleTest framework.

Tests include:

Buffer starts empty.

Producing a single item increases the size.

Consuming an item decreases the size.

To run unit tests with Cmake:

use ctest from build directory or ./tests on Linux / Debug\tests.exe on Windows

### Key Concepts

- std::mutex – Protects shared buffer.
- std::unique_lock – Flexible lock for condition variables.
- std::condition_variable – Waits for buffer conditions.
- Thread Sleep – Simulates production/consumption delays.

