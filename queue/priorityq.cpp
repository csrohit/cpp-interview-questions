#include <cstdio>
#include <queue>


using namespace std;

int main()
{
    priority_queue<int> q;

    q.push(10);
    q.push(3);
    q.push(8);
    q.push(2);

    while(!q.empty())
    {
        printf("%-4d", q.top());
        q.pop();
    }
    printf("\n");
    
    return (0);
}
