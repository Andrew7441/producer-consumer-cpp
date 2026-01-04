/*
// Buffer Not Full Scenario
#include<iostream>
#include<mutex>
#include<thread>
#include<queue>
#include<condition_variable>
#include<chrono>

std::mutex glock;																// Mutex for synchronization
std::condition_variable cond_var;												// Condition Variable for producer-consumer signaling
std::queue<int> buffer;															// Queue acts as a buffer
const unsigned int MAX_BUFFER_SIZE = 10;										// Max size of buffer


void producer(int value) {
	std::unique_lock<std::mutex> lock(glock);									// Lock the mutex
	cond_var.wait(lock,[]() { return buffer.size() < MAX_BUFFER_SIZE; });		// Wait until there is space in the buffer
	
	buffer.push(value);

	std::cout << "Producing: " << value << std::endl;
	std::cout << "Buffer Size after produce: " << buffer.size() << std::endl;
	
	lock.unlock();																// Unlock the mutex
	cond_var.notify_one();														// Notify one waiting thread

	std::this_thread::sleep_for(std::chrono::seconds(2));						// Simulate work/production time
}

void consumer() {
	std::unique_lock<std::mutex> lock(glock);
	cond_var.wait(lock, []() { return buffer.size() > 0; });					// Wait until there is something in the buffer

	int value = buffer.front();
	buffer.pop();

	std::cout << "Consuming: " << value << std::endl;
	std::cout << "Buffer Size after consume: " << buffer.size() << std::endl;

	lock.unlock();
	cond_var.notify_one();

	using namespace std::chrono_literals;										// Another Way to make thread sleep

	std::this_thread::sleep_for(2000ms);					    
}

int main() {

	std::thread producerthread([](){
		for (int i = 1; i <= 20; i++) {
			producer(i);					// Create a thread to produce values
		}
	});
	
	std::thread consumerthread([]() {
		for (int i = 1; i <= 20; i++) {
			consumer();					   
		}
	});

	producerthread.join();				   // Wait for producer thread to finish
	consumerthread.join();				   

	std::cout << "Main Program Execution..." << std::endl;

	return 0;
}
*/


// Buffer Full Scenario
#include<iostream>
#include<mutex>
#include<thread>
#include<queue>
#include<condition_variable>
#include<chrono>

std::mutex glock;																// Mutex for synchronization
std::condition_variable cond_var;												// Condition Variable for producer-consumer signaling
std::queue<int> buffer;															// Queue acts as a buffer
const unsigned int MAX_BUFFER_SIZE = 10;										// Max size of buffer


void producer(int value) {
	std::unique_lock<std::mutex> lock(glock);									// Lock the mutex
	cond_var.wait(lock, []() { return buffer.size() < MAX_BUFFER_SIZE; });		// Wait until there is space in the buffer

	buffer.push(value);

	std::cout << "Producing: " << value << std::endl;
	std::cout << "Buffer Size after produce: " << buffer.size() << std::endl;

	lock.unlock();																// Unlock the mutex
	cond_var.notify_one();														// Notify one waiting thread

}

void consumer() {
	std::unique_lock<std::mutex> lock(glock);
	cond_var.wait(lock, []() { return buffer.size() > 0; });					// Wait until there is something in the buffer

	int value = buffer.front();
	buffer.pop();

	std::cout << "Consuming: " << value << std::endl;
	std::cout << "Buffer Size after consume: " << buffer.size() << std::endl;

	lock.unlock();
	cond_var.notify_one();


}

int main() {

	std::thread producerthread([]() {
		for (int i = 1; i <= 20; i++) {
			producer(i);					// Create a thread to produce values
		}
		});


	std::this_thread::sleep_for(std::chrono::seconds(3));	// Delay before starting consumer thread

	std::thread consumerthread([]() {
		for (int i = 1; i <= 20; i++) {
			consumer();
		}
		});

	producerthread.join();				   // Wait for producer thread to finish
	consumerthread.join();

	std::cout << "Main Program Execution..." << std::endl;

	return 0;
}
