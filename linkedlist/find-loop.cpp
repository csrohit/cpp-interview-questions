#include <cstdint>
#include <cstdio>
#include "linked-list.h"

const Node* const findLoop(Node* const head)
{
    const Node* slow    = head;
    const Node* fast    = head;
    bool        bIsLoop = false;

    if (nullptr == head)
    {
        // do nothing
    }
    else
    {
        while ((nullptr != slow) && (nullptr != fast) && (nullptr != fast->next))
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                bIsLoop = true;
                break;
            }
        }
    }
    if (true == bIsLoop)
    {
        return const_cast<const Node* const>(fast);
    }
    else
    {
        return nullptr;
    }
}

int main()
{
    Node* const head = readList();

    // Node* const middle = findLoop(head);
    Node* tail = getTail(head);
    printf("Tail Node: %d\n", tail->data);

    const Node* const node = getNodeAtVal(head, 6);
    printf("Val Node: %d\n", node->data);

    printList(head);

    tail->next = const_cast<Node*>(node->next);

    const Node* const loopNode = findLoop(head);
    printf("Val Node: %d\n", loopNode->data);

    tail->next = nullptr;

    freeList(head);

    return (0);
}
