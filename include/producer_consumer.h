#pragma once
#include <cstddef>

void produce_one(int value);       // push a value into the buffer (thread-safe)
void consume_one();                 // pop a value, return -1 if empty
void reset_buffer();               // clear buffer (used by tests)
bool buffer_empty();               // true if empty
std::size_t buffer_size();         // current size
