#include <cstdint>
#include <cstdio>
#include "linked-list.h"

Node* const reverse(Node* const head, uint32_t posLeft, uint32_t posRight)
{
    if ((nullptr == head) || (posLeft == posRight))
    {
        //
    }
    else
    {
        Node* prev    = nullptr;
        Node* current = head;
        Node* newTail = nullptr;

        for (uint32_t idx = 0; (nullptr != current) && (idx < posLeft); ++idx)
        {
            prev    = current;
            current = current->next;
        }

        newTail = current;
        Node* next = nullptr;
        for (uint32_t idx = posLeft; (nullptr != current) && (idx < posLeft); ++idx) {
            next = current->next;
            current->next = newTail;
            newTail = current;
            current = next;
        }
        prev->next = newTail;
    }
    return head;
}

int main()
{
    Node* const head = readList();
    printList(head);

    Node* const middle = reverse(head, 2, 5);

    printList(middle);
    freeList(head);

    return (0);
}
