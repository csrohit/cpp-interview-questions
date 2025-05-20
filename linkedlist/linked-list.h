#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstdint>
#include <cstdio>
#include <ostream>

using std::count;
using std::ostream;
class Node
{
  public:
    int   val;
    Node* next;

    Node(int d) : val(d), next(nullptr) {};

    friend ostream& operator<<(ostream& os, const Node& node);
};

class LinkedList
{
  public:
    Node* head;
    Node* tail;

    LinkedList() : head(nullptr), tail(nullptr) {};

    void insert(int val)
    {
        Node* node = new Node(val);

        if (nullptr == head)
        {
            head = node;
            tail = head;
        }
        else
        {
            tail->next = node;
            tail       = tail->next;
        }
    }

    ~LinkedList()
    {
        Node* node = head;
        while (nullptr != node)
        {
            Node* next = node->next;
            delete node;
            node = next;
        }

        head = nullptr;
    }

    friend ostream& operator<<(ostream& os, const LinkedList& node);
};

#endif
