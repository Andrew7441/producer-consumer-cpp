#include "producer_consumer.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

// "Buffer Not Full" scenario:
// Producer and consumer run concurrently.
static void run_buffer_not_full_scenario()
{
    std::cout << "Running: Buffer Not Full scenario\n";

    std::thread producer_thread([] {
        for (int i = 1; i <= 20; ++i) {
            produce_one(i);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        });
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread consumer_thread([] {
        for (int i = 1; i <= 20; ++i) {
            consume_one();
            std::this_thread::sleep_for(std::chrono::seconds(2));

        }
        });

    producer_thread.join();
    consumer_thread.join();

    std::cout << "Finished: Buffer Not Full scenario\n";
}

// "Buffer Full" scenario:
// Producer and consumer 
static void run_buffer_full_scenario()
{
    std::cout << "Running: Buffer Full scenario\n";

    std::thread producer_thread([] {
        for (int i = 1; i <= 20; ++i) {
            produce_one(i);
        }
        });

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::thread consumer_thread([] {
        for (int i = 1; i <= 20; ++i) {
            consume_one();
        }
        });

    producer_thread.join();
    consumer_thread.join();

    std::cout << "Finished: Buffer Full scenario\n";
}

int main(int argc, char** argv)
{
    
    std::string mode = "full";
    if (argc > 1) mode = argv[1];

    if (mode == "full" || mode == "buffer-full" || mode == "buffer_full") {
        run_buffer_full_scenario();
    }
    else if (mode == "not-full" || mode == "buffer-not-full" || mode == "not_full") {
        run_buffer_not_full_scenario();
    }
    else {
        std::cout << "Unknown mode: " << mode << "\n";
        std::cout << "Usage:\n"
            << "  " << argv[0] << "            # default: not-full\n"
            << "  " << argv[0] << " not-full\n"
            << "  " << argv[0] << " full\n";
        return 1;
    }

    std::cout << "Main Program Execution complete.\n";
    return 0;
}

