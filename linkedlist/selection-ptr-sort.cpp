#include <cstdio>

class Node
{
    public:
    int   data;
    Node* next;

    Node(int d) : data(d), next(nullptr) {};
};

Node* selectionSort(Node* head)
{
    Node* sortedHead = nullptr;
    Node* sortedTail = nullptr;

    while (nullptr != head)
    {
        Node* min     = head;
        Node* prevMin = nullptr;
        Node* prev    = head;

        while (nullptr != prev && nullptr != prev->next)
        {
            if (min->data > prev->next->data)
            {
                min     = prev->next;
                prevMin = prev;
            }
            prev = prev->next;
        }

        if (nullptr != prevMin)
        {
            prevMin->next = min->next;
        }
        else
        {
            head = min->next;
        }

        if (nullptr == sortedHead)
        {
            sortedHead = min;
            sortedTail = min;
        }
        else
        {
            sortedTail->next = min;
            sortedTail       = min;
        }
        min->next = nullptr;
    }

    return sortedHead;
}
void printList(Node* head)
{
    for (Node* itr = head; nullptr != itr; itr = itr->next)
    {
        printf("-> %d ", itr->data);
    }
    printf("\n");
}

int main()
{
    Node* head = new Node(5);
    head->next                   = new Node(4);
    head->next->next             = new Node(3);
    head->next->next->next       = new Node(2);
    head->next->next->next->next = new Node(1);

    printList(head);
    head = selectionSort(head);
    printList(head);

    delete head->next->next->next->next;
    delete head->next->next->next->next;
    delete head->next->next->next;
    delete head->next->next;
    delete head->next;
}
