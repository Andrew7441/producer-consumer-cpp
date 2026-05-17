#include "producer_consumer.h"

#include <chrono> // provides time durations like seconds
#include <iostream> 
#include <string>
#include <thread> // provides thread and sleep for

using namespace std;

// "Buffer Not Full" scenario:
// Producer and consumer run concurrently.
static void run_buffer_not_full_scenario()
{
    std::cout << "Running: Buffer Not Full scenario\n";

    std::thread producer_thread([] {   //starts the producer thread
        for (int i = 1; i <= 20; ++i) {
            produce_one(i); // produce values from 1 - 20
            std::this_thread::sleep_for(std::chrono::seconds(2)); // slows producer down
        }
    });
    
    std::this_thread::sleep_for(std::chrono::seconds(2));  //delay consumer start
    
    std::thread consumer_thread([] { // start the consumer thread
        for (int i = 1; i <= 20; ++i) {
            consume_one(); // removes one value from the buffer
            std::this_thread::sleep_for(std::chrono::seconds(2)); // then sleep

        }
    });
        
    //call join so the main thread waits for the worker thread to finish before continuing/exiting
    //if i dont call join main might finish before thrad finish
    producer_thread.join(); // waits for producer thread to finish 
    consumer_thread.join(); // waits for consumer thread to finish

    std::cout << "Finished: Buffer Not Full scenario\n";
}

// "Buffer Full" scenario:
// Producer and consumer 
static void run_buffer_full_scenario()
{
    std::cout << "Running: Buffer Full scenario\n";

    std::thread producer_thread([] { // starts the producer thread
        for (int i = 1; i <= 20; ++i) {
            produce_one(i);
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(3)); // lets producer fill the buffer first

    std::thread consumer_thread([] { // starts the consumer thread
        for (int i = 1; i <= 20; ++i) {
            consume_one();
        }
    });

    //wait for producer and consumer thread to finish before continuing on main thread
    producer_thread.join();
    consumer_thread.join();

    std::cout << "Finished: Buffer Full scenario\n";
}

int main()
{
    std::string mode;
    cout << "Which mode do you want? (full/not-full): ";
    cin >> mode;
    

    if (mode == "full" || mode == "buffer-full" || mode == "buffer_full") {
        run_buffer_full_scenario();
    }
    else if (mode == "not-full" || mode == "buffer-not-full" || mode == "not_full") {
        run_buffer_not_full_scenario();
    }
    else {
        std::cout << "Unknown mode: " << mode << "\n";
        return 1;
    }

    std::cout << "Main Program Execution complete.\n";
    return 0;
}
/*
Thread ordering is not guaranteed because the OS decides which thread runs at each moment. 
Even if i created the producer first then consumer second, once both exist, the OS scheduler can choose either one
Thread execution order is nondeterministic. Creating a thread first does not guarantee it will run first or finish first. The OS scheduler controls when each thread runs, so outputs from multiple threads can appear in different valid orders.
*/
