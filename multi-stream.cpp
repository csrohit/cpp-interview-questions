#include <cstdio>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <condition_variable>

#define NUM_STREAMS 4

class MultiStream
{
    private:
    public:
};


std::vector<std::mutex> thread_mutexes(4);

class StreamMonitor
{
    private:
    std::vector<std::thread> consumers;
    std::atomic<bool> isRuning;
    std::condition_variable cv;

    void consume(uint32_t streamIdx)
    {
        std::unique_lock lock(thread_mutexes[streamIdx]);
        cv.wait(lock);

        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());

        printf("Hello from thread %u %lld\n", streamIdx, ms.count());

    }

    public:
    void StartAll()
    {


        for (uint8_t idx = 0U; idx < NUM_STREAMS; ++idx)
        {
            consumers.emplace_back(&StreamMonitor::consume, this, idx);
        }

    }

    void StopAll()
    {
        /* terminate thread loops */
        isRuning.store(false);

        /* Release threads from wait if blocked */
        cv.notify_all();

        /* join all threads */
        for (auto&  consumer: consumers)
        {
            if (consumer.joinable())
            {
                consumer.join();
            }
        }
    }

    void signalConsumption()
    {
        cv.notify_all();
    }
};

int main()
{
    StreamMonitor monitor;

    monitor.StartAll();

    for (uint32_t idx = 0; idx < 10; ++idx)
    {
        monitor.signalConsumption();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }


    monitor.StopAll();

    return (0);
}
