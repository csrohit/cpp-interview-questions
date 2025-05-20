#include "linked-list.h"
#include <cstdint>
#include <cstdio>
#include <iostream>

Node* const reverse(LinkedList& list, uint32_t posLeft, uint32_t posRight)
{
    if ((nullptr == list.head) || (posLeft == posRight))
    {
        //
    }
    else
    {
        Node* start   = nullptr;
        Node* prev   = nullptr;
        Node* current = list.head;
        Node* newTail = nullptr;

        for (uint32_t idx = 1; (nullptr != current) && (idx < posLeft); ++idx)
        {
            prev = current;
            current = current->next;
        }

        start = current;
        newTail    = current;
        Node* next = nullptr;
        for (uint32_t idx = 0U; (nullptr != current) && (idx <= (posRight - posLeft)); ++idx)
        {
            next          = current->next;
            current->next = newTail;
            printf("Linking %d -> %d\n", current->data, newTail->data);
            newTail = current;
            current = next;
        }


        /* Reverse from list.head */
        if (nullptr == prev)
        {
            // printf("Prev: %d, start: %d, newTail %d, current %d\n", 0, start->data, newTail->data, current->data);
            list.head = newTail;
        }
        else
        {
            // printf("Prev: %d, start: %d, newTail %d, current %d\n", prev->data, start->data, newTail->data, current->data);
            prev->next = newTail;
        }

        /* Initial node is prev->next */
        start->next = current;
    }
    return list.head;
}

int main()
{
    LinkedList list;

    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);
    list.insert(7);
    list.insert(8);

    std::cout << "List: " << list << std::endl;

    printf("Reversing list from %d -> %d\n", 1, 1);

    reverse(list, 2, 4);

    std::cout << "List: " << list << std::endl;

    return (0);
}
