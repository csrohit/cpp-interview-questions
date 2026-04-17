#include <cstdint>
#include <cstdio>
#include "linked-list.h"

/**
 * Find the middle node of a singly linked list using a single pass.
 * The algorithm advances the middle pointer every second step.
 *
 * @param head The head of the linked list.
 * @return Pointer to the middle node, or nullptr for an empty list.
 */
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
        for (int idx = 1; nullptr != temp; temp = temp->next, ++idx)
        {
            if (0 == (idx & 1))
            {
                middle = middle->next;
            }
        }
    }

    return const_cast<Node*>(middle);
}

/**
 * Read a list from stdin, print it, and display its middle element.
 */
int main()
{
    Node* const head = readList();
    printList(head);

    Node* const middle = getMiddle(head);
    if (nullptr != middle)
    {
        printf("Middle element is : %d\n", middle->val);
    }

    freeList(head);
    
    return 0;
}
