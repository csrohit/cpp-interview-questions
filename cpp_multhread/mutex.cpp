#include <cstdio>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

std::mutex mtx;

void thread_guard(int threadId)
{
    lock_guard guard(mtx);

    printf("Thread%d: Started\n", threadId);
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    printf("Thread%d: Finished\n", threadId);
}

void thread_unique(int threadId)
{
    std::unique_lock lock(mtx);

    printf("Thread%d: Started\n", threadId);
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    printf("Thread%d: Finished\n", threadId);
}

void thread_handler(int threadId)
{
    mtx.lock();
    printf("Thread%d: Started\n", threadId);
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    printf("Thread%d: Finished\n", threadId);
    mtx.unlock();
}



int main()
{
    thread t1(thread_handler, 1);   
    thread t2(thread_unique, 2);   
    thread t3(thread_guard, 3);   
    thread t4(thread_handler, 4);   
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
