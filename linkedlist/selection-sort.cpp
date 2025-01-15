#include <cstdio>
#include <algorithm>

using namespace std;

template <class T> class Node
{
    public:
    T     data;
    Node* next;

    Node(T d) : data(d), next(nullptr) {};
};

template <typename T> Node<T>* selectionSort(Node<T>* head)
{
    for (Node<T>* itr = head; nullptr != itr; itr = itr->next)
    {
        Node<T>* min = itr;

        for (Node<T>* node = itr->next; nullptr != node; node = node->next)
        {
            if (min->data > node->data)
            {
                min = node;
            }
        }

        if (min != itr)
        {
            swap(itr->data, min->data);
        }
    }

    return head;
}

template <typename T>
void printList(Node<T>* head)
{
    for (Node<T>* itr = head; nullptr != itr; itr = itr->next)
    {
        printf("-> %d ", itr->data);
    }
    printf("\n");
}

int main()
{
    Node<int> head(5);
    head.next             = new Node<int>(4);
    head.next->next       = new Node<int>(3);
    head.next->next->next = new Node<int>(2);
    head.next->next->next->next = new Node<int>(1);

    printList(&head);
    selectionSort(&head);
    printList(&head);

    delete head.next->next->next->next;
    delete head.next->next->next;
    delete head.next->next;
    delete head.next;
    return (0);
}
