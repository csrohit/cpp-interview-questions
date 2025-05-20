/*
    2 threads access same resource,
    1 - Increment
    2 - decrement


*/

#include<cstdio>
#include <thread>

using namespace std;

int counter = 100;

mutex mtx;
bool bTerminate = false;

void increment()
{
    while (false == bTerminate)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
        unique_lock lock(mtx);
        counter++;
        printf("%-10s: count = %d\n", __func__, counter);
    }
}

void decrement()
{
    while (false == bTerminate)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
        unique_lock lock(mtx);
        counter--;
        printf("%-10s: count = %d\n", __func__, counter);
    }
}

int main()
{

    thread incrThread(increment);
    thread decrThread(decrement);


    this_thread::sleep_for(chrono::seconds(10));
    
    bTerminate = true;

    incrThread.join();
    decrThread.join();

    return 0;
}

