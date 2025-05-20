

#include <iostream>
#include <ostream>
#include <vector>

namespace rohit_c
{
template <typename T> class Stack
{
  private:
    struct Node
    {
      public:
        T     data;
        Node *next;

        Node(T d): data(d), next(nullptr){};
    };

    Node* topNode;

    public:
    Stack(): topNode(nullptr){};
    ~Stack()
    {
        while(!empty())
        {
            Node* node = topNode;
            topNode = topNode->next;
            delete node;
        }
    }

    void push(T data)
    {
        Node* node = new Node(data);
        if (!empty())
        {
            node->next = topNode;
        }
        topNode = node;
    }

    T top() const
    {
        if (empty())
        {
            std::cerr << "Stack is empty" << std::endl;
            return 0;
        }
        return topNode->data;
    }

    void pop()
    {
        if (empty())
        {
            std::cerr << "Stack is empty" << std::endl;
            return ;
        }
        Node* node = topNode;
        topNode = topNode->next;
        delete node;
    }

    bool empty() const
    {
        return (nullptr == topNode);
    }
};
} // namespace rohit_c
