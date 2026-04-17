#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

/**
 * Simple thread pool implementation.
 * Worker threads fetch tasks from a shared queue and execute them.
 * The queue is protected by a mutex and a condition variable is used to
 * wake workers when new tasks arrive or when shutdown is requested.
 */
class ThreadPool
{
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread>        workers;

    std::mutex              mQueue;
    std::condition_variable cv;
    std::atomic<bool>       stop;

    /**
     * Worker loop that repeatedly fetches tasks and executes them.
     * When fetchTask() returns a null function, it means the pool is stopping.
     */
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
    /**
     * Create the thread pool with the specified number of worker threads.
     * Each worker thread runs ThreadPool::doWork().
     *
     * @param numThreads Number of threads to create in the pool.
     */
    explicit ThreadPool(size_t numThreads) : stop(false)
    {
        for (size_t idx = 0U; idx < numThreads; ++idx)
        {
            workers.emplace_back(&ThreadPool::doWork, this);
        }
    }

    /**
     * Shutdown the pool by setting the stop flag, waking all workers,
     * and joining each thread.
     */
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

    /**
     * Enqueue a new task for execution.
     * The task is moved into the shared queue while holding the mutex.
     * notify_one() wakes one waiting worker thread to process the task.
     *
     * @param task The callable to execute later.
     */
    void enqueue(std::function<void()> task)
    {
        {
            std::lock_guard<std::mutex> lock(mQueue);
            tasks.push(std::move(task));
        }
        cv.notify_one();
    }

    /**
     * Fetch the next available task from the queue.
     * Waits until either stop is true or the queue contains a task.
     *
     * @return The next task, or nullptr when the pool is shutting down.
     */
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


/**
 * Example task function that prints the task id and simulates work.
 *
 * @param taskId Numeric identifier for the task being executed.
 */
void completeTask(uint32_t taskId)
{
    std::cout << "Thread " << std::this_thread::get_id() << " is processing task " << taskId << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

/**
 * Create a thread pool, enqueue tasks, and demonstrate parallel execution.
 */
int main()
{
    /*
     * Create a pool with 4 worker threads.
     */
    ThreadPool pool(4);
    
    /*
     * Enqueue 11 tasks. Each task captures idx by value and executes later.
     */
    for (uint32_t idx = 0;  idx <= 10; ++idx) {
        pool.enqueue([idx]() { completeTask(idx); });
    }

    std::cout << "Main thread finished\n";

    return 0;
}
