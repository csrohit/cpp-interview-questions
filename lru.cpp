#include <iostream>

using namespace std;

class Node
{
    private:
    public:
    int   key;
    int   value;
    Node* prev;
    Node* next;

    Node(int key, int value);
};

Node::Node(int key, int value)
{
    this->key   = key;
    this->value = value;
    this->prev  = nullptr;
    this->next  = nullptr;
}

class LRUCache
{
    public:
    int   capacity;
    Node* head;
    Node* tail;

    unordered_map<int, Node*> cacheMap;

    LRUCache(int capacity);
    void put(int key, int value);
    int  get(int key);
    void remove(Node* node);
    void add(Node* node);
    void print();
};

LRUCache::LRUCache(int capacity)
{
    this->capacity = capacity;
    head           = new Node(-1, -1);
    tail           = new Node(-1, -1);
    head->next     = tail;
    tail->prev     = head;
}

void LRUCache::add(Node* node)
{
    Node* temp = head->next;
    head->next = node;
    node->next = temp;
    node->prev = head;
    temp->prev = node;
}

void LRUCache::remove(Node* node)
{
    Node* prevNode = node->prev;
    Node* nextNode = node->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
}

int LRUCache::get(int key)
{
    if (cacheMap.find(key) == cacheMap.end())
    {
        return -1;
    }
    Node* node = cacheMap[key];
    remove(node);
    add(node);
    return node->value;
}

void LRUCache::put(int key, int value)
{
    /* Ndde already exists */
    if (cacheMap.find(key) != cacheMap.end())
    {
        Node* node = cacheMap[key];
        remove(node);
        node->value = value;
        printf("Updating node %d->%d with node: %d->%d\n", node->key, node->value, key, value);
        add(node);
    }
    else
    {
        /* Key does not exist but map is full */
        if (cacheMap.size() >= capacity)
        {
            Node* node = tail->prev;
            remove(node);
            printf("Replacing node %d->%d with node: %d->%d\n", node->key, node->value, key, value);
            node->key   = key;
            node->value = value;
            add(node);
        }
        else
        {
            /* Key does not exist but map is not full */
            Node* node = new Node(key, value);
            printf("Adding a new node: %d->%d\n", key, value);
            cacheMap[key] = node;
            node->key     = key;
            node->value   = value;
            add(node);
        }
    }
}

void LRUCache::print()
{
    Node* node = head->next;
    printf("Cache: \n");

    while (tail != node)
    {
        printf("%d -> %d\n", node->key, node->value);
        node = node->next;
    }
}

int main()
{
    LRUCache cache(2);

    cache.print();
    cache.put(1, 1);
    cache.print();
    cache.put(2, 2);
    cache.print();
    cout << cache.get(1) << endl;
    cache.print();
    cache.put(3, 3);
    cache.print();
    cout << cache.get(2) << endl;
    cache.print();
    cache.put(4, 4);
    cache.print();
    cout << cache.get(1) << endl;
    cache.print();
    cout << cache.get(3) << endl;
    cache.print();
    cout << cache.get(4) << endl;
    cache.print();
    return (0);
}
