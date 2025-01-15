#include <cstdio>
#include <thread>

using namespace std;

struct Point
{
    int x;
};


void thread_handler(Point& point)
{
    printf("%-20s: point.x = %d\n", __func__, point.x);
    point.x = 30;
}


int main()
{
    Point point;
    point.x = 20;
    printf("%-20s: point.x = %d\n", __func__, point.x);

    thread t(thread_handler, ref(point));
    t.join();
    printf("%-20s: point.x = %d\n", __func__, point.x);
    return 0;
}
