#include <cstdio>
#include "stack.h"
#include "queue.h"

// using namespace rohit_c;

int main()
{

    rohit_c::Stack<int> stack;

    stack.push(10);
    stack.push(11);
    stack.push(12);
    stack.push(13);
    stack.pop();

    printf("Top: %d\n", stack.top());


    rohit::Queue<int> q;

    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(6);

    printf("DeQueue: %d\n", q.dequeue());
    printf("DeQueue: %d\n", q.dequeue());
    printf("DeQueue: %d\n", q.dequeue());



    return 0;
}
