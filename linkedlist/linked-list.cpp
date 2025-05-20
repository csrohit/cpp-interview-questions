
#include "linked-list.h"


ostream& operator<<(ostream& os, const Node& node)
{
    os << node.data;
    return os;
}


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

