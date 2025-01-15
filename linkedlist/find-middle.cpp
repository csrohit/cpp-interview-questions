#include <cstdint>
#include <cstdio>
#include "linked-list.h"


Node* const getMiddle(const Node* const head)
{
    const Node* temp   = head;
    const Node* middle = temp;

    if (nullptr == head)
    {
        return const_cast<Node*>(temp);
    }
    else
    {
        for (int idx = 1; nullptr != temp; temp = temp->next,++idx)
        {
            if (0 == (idx & 1))
            {
                middle = middle->next;
            }
        }
    }

    return const_cast<Node*>(middle);
}
int main()
{
    Node* const head = readList();
    printList(head);

    Node* const middle = getMiddle(head);
    if(nullptr != middle)
    {
        printf("Middle element is : %d\n", middle->data);
    }

    freeList(head);
    
    return (0);
}
