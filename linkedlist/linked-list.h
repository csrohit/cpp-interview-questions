#ifndef LINKED_LIST_H
#define LINKED_LIST_H
class Node
{
    public:
    int   data;
    Node* next;

    Node(int d) : data(d), next(nullptr) {};
};

Node* const readList();
void freeList(Node* head);
void printList(const Node* const head);
Node* const getTail(const Node* const head);
const Node* const getNodeAtVal(const Node* const head, const int val);
#endif // !LINKED_LIST_H
