#pragma once
#include <cstddef>

void produce_one(int value);       
void consume_one();                 
void reset_buffer();               
bool buffer_empty();               
std::size_t buffer_size();         
