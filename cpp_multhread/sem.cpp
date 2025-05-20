#include <cstdio>
#include <semaphore>
#include <thread>
#include <chrono>

using namespace std;

binary_semaphore semaphore(0);

void thread_hander(int threadId)
{
    printf("Thread %d: Initialized\n", threadId);

    semaphore.acquire();
    printf("Thread %d: Started\n", threadId);
    this_thread::sleep_for(chrono::milliseconds(1000));
    printf("Thread %d: Finished\n", threadId);
    semaphore.release();
}

int main()
{
    thread t1(thread_hander, 1);
    thread t2(thread_hander, 2);
    thread t3(thread_hander, 3);
    thread t4(thread_hander, 4);

    this_thread::sleep_for(chrono::milliseconds(10));
    semaphore.release();
    semaphore.release();
    semaphore.release();

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return (0);
}
