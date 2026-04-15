#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool
{
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread>        workers;

    std::mutex              mQueue;
    std::condition_variable cv;
    std::atomic<bool>       stop;

    void doWork()
    {
        while (true)
        {
            std::function<void()> task = fetchTask();

            if (!task)
            {
                break;
            }
            task();
        }
    }

  public:
    explicit ThreadPool(size_t numThreads) : stop(false)
    {
        for (size_t idx = 0U; idx < numThreads; ++idx)
        {
            workers.emplace_back(&ThreadPool::doWork, this);
        }
    }

    ~ThreadPool()
    {
        stop = true;
        cv.notify_all();

        for (std::thread& worker : workers)
        {
            if (worker.joinable())
            {
                worker.join();
            }
        }
    }

    void enqueue(std::function<void()> task)
    {
        {
            std::lock_guard<std::mutex> lock(mQueue);
            tasks.push(std::move(task));
        }
        cv.notify_one();
    }

    std::function<void()> fetchTask()
    {
        std::unique_lock<std::mutex> lock(mQueue);
        cv.wait(lock, [this](){ return stop || !tasks.empty();});

        if (stop && tasks.empty())
        {
            return nullptr;
        }

        std::function<void()> task = std::move(tasks.front());
        tasks.pop();
        return task;
    }
};


void completeTask(uint32_t taskId)
{
    std::cout << "Thread " << std::this_thread::get_id() << " is processing task " << taskId << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main()
{

    ThreadPool pool(4);
    
    for (uint32_t idx = 0;  idx <= 10; ++idx) {
        pool.enqueue([idx]() {completeTask(idx);});
    }

    std::cout << "Main thread finished\n";

    return 0;
}
