
#include <cstdint>
#include <cstdio>
#include "linked-list.h"


const Node* const getNodeAtVal(const Node* const head, const int val)
{
    const Node* temp = head;

    while (nullptr != temp) {
        if(val == temp->data)
        {
            break;
        }
        temp = temp->next;
    }

    return const_cast<const Node* const>(temp);
}

Node* const getTail(const Node* const head)
{
    if(nullptr == head)
    {
        return nullptr;
    }
    const Node* temp = const_cast<const Node*>(head);
    while (nullptr != temp->next) {
        temp = temp->next;
    }

    return const_cast<Node* const>(temp);
}

void printList(const Node* const head)
{
    const Node* temp = const_cast<const Node*>(head);
    while (nullptr != temp)
    {
        printf("-> %d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(Node* head)
{
    if (nullptr == head)
    {
        return;
    }
    Node* prev = nullptr;
    Node* next = head;

    while (nullptr != next)
    {
        prev = next;
        next = next->next;
        delete prev;
    }
}

Node* const readList()
{
    Node* head = nullptr;
    Node* temp = nullptr;

    uint32_t nNodes = 0;
    printf("Enter number of elements:");
    scanf("%u", &nNodes);

    for (uint32_t idx = 0; idx < nNodes; ++idx)
    {
        if (nullptr == head)
        {
            head = new Node(0);
            temp = head;
        }
        else
        {
            temp->next = new Node(0);
            temp       = temp->next;
        }
        scanf("%d", &temp->data);
    }
    return const_cast<Node* const>(head);
}
