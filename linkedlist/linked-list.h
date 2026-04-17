#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstdint>
#include <cstdio>
#include <ostream>

using std::ostream;
/**
 * Node represents a singly linked list element.
 * It stores an integer value and a pointer to the next node.
 */
class Node
{
  public:
    int   val;
    Node* next;

    /**
     * Construct a node with the given integer value.
     * @param d The value stored in the node.
     */
    Node(int d) : val(d), next(nullptr) {};

    /**
     * Print the node value to the provided output stream.
     */
    friend ostream& operator<<(ostream& os, const Node& node);
};

/**
 * Singly linked list helper class.
 * Maintains pointers to both head and tail to allow efficient insertion.
 */
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

    /**
     * Print the list contents using the provided output stream.
     */
    friend ostream& operator<<(ostream& os, const LinkedList& node);
};

/**
 * Read integer values from standard input until EOF and build a linked list.
 * Each integer becomes a new Node appended to the list.
 * @return Pointer to the head of the created list.
 */
Node* readList();

/**
 * Print the values in the list in order.
 * @param head The head of the list to print.
 */
void printList(Node* head);

/**
 * Free all nodes in the list and release allocated memory.
 * @param head The head of the list to free.
 */
void freeList(Node* head);

#endif
