
#include "linked-list.h"

/**
 * Output the contents of a single node.
 */
ostream& operator<<(ostream& os, const Node& node)
{
    os << node.val;
    return os;
}

/**
 * Output a linked list in a readable arrow-separated format.
 */
ostream& operator<<(ostream& os, const LinkedList& list)
{
    Node* node = list.head;

    while (nullptr != node)
    {
        os << " -> " << *node;
        node = node->next;
    }
    return os;
}

/**
 * Read a fixed number of integers from stdin and build a linked list.
 * First input must be the number of items, followed by that many values.
 * Example input: 5 1 2 3 4 5
 */
Node* readList()
{
    int count;
    if (scanf("%d", &count) != 1 || count <= 0)
    {
        return nullptr;
    }

    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < count; ++i)
    {
        int value;
        if (scanf("%d", &value) != 1)
        {
            break;
        }

        Node* node = new Node(value);
        if (nullptr == head)
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

void printList(Node* head)
{
    Node* node = head;
    while (nullptr != node)
    {
        printf("%d", node->val);
        if (nullptr != node->next)
        {
            printf(" -> ");
        }
        node = node->next;
    }
    printf("\n");
}

/**
 * Delete every node in the list and release allocated memory.
 */
void freeList(Node* head)
{
    while (nullptr != head)
    {
        Node* next = head->next;
        delete head;
        head = next;
    }
}
