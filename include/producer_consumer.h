#pragma once
#include <cstddef>

void produce_one(int value);  // add a value to the shared buffer
void consume_one();           //remves one value from the shared buffer
void reset_buffer();          //clears the shared buffer
bool buffer_empty();          //returns true if the buffer is empty
std::size_t buffer_size();    //returns the number of items in the buffer