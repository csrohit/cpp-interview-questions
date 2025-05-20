#include <iostream>
#include <ostream>

namespace rohit
{
template <typename T> class Queue
{
  private:
    class Node
    {
      public:
        T     data;
        Node *next;

        Node(T d) : data(d), next(nullptr) {};
    };

    bool empty() const
    {
        return ((nullptr == head) && (head == tail));
    }

    Node *head;
    Node *tail;

    public:

    Queue() : head(nullptr), tail(nullptr) {};

    ~Queue()
    {
        while (nullptr != head)
        {
            Node* node = head;
            head = head->next;
            delete node;
        }
        tail = nullptr;
    }

    void enqueue(T d)
    {
        Node *node = new Node(d);

        if (!empty())
        {
            tail->next = node;
        }
        else
        {
            head = node;
        }
        tail = node;
    }

    T dequeue()
    {
        if (empty())
        {
            std::cerr << "Queue is empty" << std::endl;
            return 0;
        }

        if (head == tail)
        {
            tail = nullptr;
        }

        Node* node = head;
        T d = node->data;
        
        head = head->next;
        delete node;
        node = nullptr;
        return d;
    }
};
} // namespace rohit
