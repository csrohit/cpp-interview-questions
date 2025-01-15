#include <cstdint>
#include <cstdio>
#include "linked-list.h"

Node* const reverse(Node* const head)
{
    Node* newHead = nullptr;
    Node* next    = head;
    Node* temp    = nullptr;

    if (nullptr == head)
    {
        // do nothing
    }
    else {
        while(nullptr != next)
        {
            temp = next;
            next = next->next;
            temp->next = newHead;
            newHead = temp;
        }
    }

    return const_cast<Node*>(newHead);
}

int main()
{
    Node* const head = readList();
    printList(head);

    Node* const middle = reverse(head);

    printList(middle);
    freeList(head);

    return (0);
}
