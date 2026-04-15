#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>

#define COUNT_MAX 20
bool isOdd = true;
std::mutex m;
std::condition_variable cv;

void odd()
{
    uint32_t counter = 1;

    // Run while counter is less than or equal to the maximum odd value.
    while (counter <= COUNT_MAX)
    {
        /*
         * Acquire the mutex guard to synchronize access to shared state.
         * std::unique_lock<std::mutex> is used because std::condition_variable
         * requires a std::unique_lock to safely unlock and relock the mutex
         * while waiting.
         */
        std::unique_lock<std::mutex> lock(m);
        
        /*
         * Wait on the condition variable until the predicate becomes true.
         * The lock is atomically released while waiting and reacquired when
         * the thread is awakened. The lambda returns true only when it is
         * the odd thread's turn to run.
         */
        cv.wait(lock, [](){ return isOdd; });

        std::cout << __func__ << ": " << counter << std::endl;
        counter += 2;
        isOdd = false;

        /*
         * Notify one waiting thread that shared state has changed.
         * This wakes the even thread so it can check the predicate and proceed.
         */
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void even()
{
    uint32_t counter = 2;

    // Run while counter is less than or equal to the maximum odd value.
    while (counter <= COUNT_MAX)
    {
        /*
         * Acquire the mutex guard to protect the shared boolean flag.
         * Using std::unique_lock allows the condition variable to release
         * the lock while waiting and reacquire it when awakened.
         */
        std::unique_lock<std::mutex> lock(m);
        
        /*
         * Wait until the shared state indicates the even thread may run.
         * The predicate is evaluated while the mutex is held and the thread
         * will only continue when it becomes false that it is the odd turn.
         */
        cv.wait(lock, [](){ return !isOdd; });

        std::cout << __func__ << ": " << counter << std::endl;
        counter += 2;
        isOdd = true;

        /*
         * Notify one waiting thread after updating the shared flag,
         * allowing the odd thread to resume its work.
         */
        cv.notify_one();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


int main()
{
    /*
     * Create two threads that execute the odd() and even() functions.
     * std::thread takes a callable object and starts execution immediately.
     */
    std::thread t1(odd);
    std::thread t2(even);

    /*
     * Wait for the first thread to complete before exiting.
     * join() blocks until the thread has finished execution.
     */
    if (t1.joinable())
    {
        t1.join();
    }

    /*
     * Wait for the second thread to complete as well.
     */
    if (t2.joinable())
    {
        t2.join();
    }

    return 0;
}
