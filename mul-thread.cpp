
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>
#include <barrier>

int getData() {
    // Simulate an API that returns a random integer
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    return dist(gen);
}

void threadTask(std::barrier<>& syncPoint, std::mutex& outputMutex, int loopCount) {
    for (int i = 0; i < loopCount; ++i) {
        // Wait until all threads reach this point
        syncPoint.arrive_and_wait();

        // Capture the timestamp
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        // Call the API
        int data = getData();

        // Safely output the result
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "Thread ID: " << std::this_thread::get_id()
                  << ", Loop: " << i
                  << ", Data: " << data
                  << ", Timestamp: " << std::ctime(&time);

        // Sleep for 100ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    constexpr int numThreads = 4;
    constexpr int loopCount = 5; // Number of times to call getData() in each thread
    std::vector<std::thread> threads;

    // Synchronization mechanisms
    std::mutex outputMutex;
    std::barrier syncPoint(numThreads);

    // Launch threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(threadTask, std::ref(syncPoint), std::ref(outputMutex), loopCount);
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
