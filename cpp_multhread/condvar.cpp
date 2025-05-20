#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <queue>
#include <thread>

using std::condition_variable;
using std::mutex;
using std::queue;
using std::thread;
using std::unique_lock;
using std::chrono::seconds;

bool g_abort = false;

class RequestManager
{
  private:
    int                capacity;
    queue<int>         _queue;
    mutex              mtx;
    condition_variable cvFull;
    condition_variable cvEmpty;

  public:
    RequestManager(int c) : capacity(c) {};

    ~RequestManager()
    {
        while (!_queue.empty())
        {
            _queue.pop();
        }
    }

    void push(int i)
    {
        unique_lock lock(mtx);

        if (capacity == _queue.size())
        {
            printf("Queue is full, waiting...\n");
            cvFull.wait_for(lock, seconds(1));

            if (capacity == _queue.size())
            {
                printf("Timed out exiting...");
                throw std::runtime_error("Queue is full");
            }
        }

        printf("Pushing into queue %d\n", i);
        _queue.push(i);
        cvEmpty.notify_one();
    }

    int pop()
    {
        unique_lock lock(mtx);

        if (_queue.empty())
        {
            printf("Queue is empty, waiting...\n");
            cvEmpty.wait_for(lock, seconds(1));

            if (_queue.empty())
            {
                printf("Timed out exiting...");
                throw std::runtime_error("Queue is Empty");
            }
        }

        int i = _queue.front();
        _queue.pop();
        printf("Popped from queue %d\n", i);

        cvFull.notify_one();

        return i;
    }
};

RequestManager manager(5);

void push()
{
    printf("Starting Push threa\n");
    int counter = 0;
    while (!g_abort)
    {
        try
        {
            manager.push(counter++);
            std::this_thread::sleep_for((std::chrono::milliseconds(500)));
        }
        catch (std::runtime_error e)
        {
            g_abort = true;
            printf("%s\n", e.what());
        }
    }

    printf("exiting from push\n");
}

void pop()
{
    printf("Starting Pop thread\n");
    int counter = 0;
    while (!g_abort)
    {
        try
        {
            manager.pop();
            std::this_thread::sleep_for((std::chrono::milliseconds(200)));
        }
        catch (std::runtime_error e)
        {
            g_abort = true;
            printf("%s\n", e.what());
        }
    }
    printf("exiting from Pop\n");
}

int main()
{

    thread t1(push);


    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    thread t2(pop);

    if (t1.joinable())
    {
        t1.join();
    }
    if (t2.joinable())
    {
        t2.join();
    }

    return 0;
}
