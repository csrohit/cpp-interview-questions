#include <iostream>
#include <unordered_map>

using namespace std;

/**
 * A doubly-linked list node used by the LRU cache.
 * Each node stores a cache key/value pair and links to its neighbors.
 */
class Node
{
    public:
    int   key;
    int   value;
    Node* prev;
    Node* next;

    /**
     * Construct a node with the given key/value pair.
     */
    Node(int key, int value);
};

Node::Node(int key, int value)
{
    this->key   = key;
    this->value = value;
    this->prev  = nullptr;
    this->next  = nullptr;
}

/**
 * A simple LRU (Least Recently Used) cache implementation.
 * It maintains a doubly-linked list for LRU ordering and an unordered_map
 * for O(1) lookup by key.
 */
class LRUCache
{
    public:
    int   capacity;
    Node* head;
    Node* tail;

    unordered_map<int, Node*> cacheMap;

    LRUCache(int capacity);

    /**
     * Insert or update the given key/value pair in the cache.
     */
    void put(int key, int value);

    /**
     * Retrieve a value for the given key.
     * If found, move the node to the head of the list to mark it as most recently used.
     * Returns -1 when the key is not present.
     */
    int  get(int key);

    /**
     * Remove the given node from its current position in the doubly-linked list.
     */
    void remove(Node* node);

    /**
     * Add the given node right after the head, making it the most recently used item.
     */
    void add(Node* node);

    /**
     * Print the current cache contents from most recently used to least recently used.
     */
    void print();
};

LRUCache::LRUCache(int capacity)
{
    this->capacity = capacity;

    // Dummy head and tail simplify insert/remove operations.
    head           = new Node(-1, -1);
    tail           = new Node(-1, -1);
    head->next     = tail;
    tail->prev     = head;
}

void LRUCache::add(Node* node)
{
    // Insert node right after head, marking it most recently used.
    Node* temp = head->next;
    head->next = node;
    node->next = temp;
    node->prev = head;
    temp->prev = node;
}

void LRUCache::remove(Node* node)
{
    // Detach the node from the linked list.
    Node* prevNode = node->prev;
    Node* nextNode = node->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
}

int LRUCache::get(int key)
{
    if (cacheMap.find(key) == cacheMap.end())
    {
        // Cache miss.
        return -1;
    }

    // Cache hit: move this node to the head as most recently used.
    Node* node = cacheMap[key];
    remove(node);
    add(node);
    return node->value;
}

void LRUCache::put(int key, int value)
{
    if (cacheMap.find(key) != cacheMap.end())
    {
        // Key already exists: update value and move node to head.
        Node* node = cacheMap[key];
        remove(node);
        node->value = value;
        printf("Updating node %d->%d with node: %d->%d\n", node->key, node->value, key, value);
        add(node);
    }
    else
    {
        if (cacheMap.size() >= capacity)
        {
            // Cache is full: evict the least recently used node.
            Node* node = tail->prev;
            remove(node);
            printf("Replacing node %d->%d with node: %d->%d\n", node->key, node->value, key, value);
            cacheMap.erase(node->key);

            node->key   = key;
            node->value = value;
            add(node);
            cacheMap[key] = node;
        }
        else
        {
            // Cache is not full: create a new node and insert it.
            Node* node = new Node(key, value);
            printf("Adding a new node: %d->%d\n", key, value);
            cacheMap[key] = node;
            add(node);
        }
    }
}

void LRUCache::print()
{
    Node* node = head->next;
    std::cout << "Cache: ";

    while (tail != node)
    {
        std::cout << "[" << node->key << ": " << node->value << "] ";
        node = node->next;
    }
    std::cout << std::endl;
}

/**
 * Print the internal hash map contents for debugging.
 * This should match the cache entries currently stored in the cache.
 */
void printMap(const std::unordered_map<int, Node*>& map)
{
    std::cout << "Map: ";
    for (const auto& pair : map)
    {
        std::cout << "[" << pair.first << ": " << pair.second->value << "] ";
    }
    std::cout << std::endl;
}

int main()
{
    LRUCache cache(2);

    // Add initial entries. Cache capacity is 2.
    cache.put(1, 101);
    cache.put(2, 102);

    // At this point the cache contains keys [2, 1] with 2 as most recently used.
    cache.print();

    // Access key 1 to move it to most recently used position.
    cout << "Fetching 1: " << cache.get(1) << endl;
    cache.print();
    cout << std::endl;

    // Insert key 3. Since the cache is full, the least recently used key (2) is evicted.
    cache.put(3, 103);
    cache.print();
    printMap(cache.cacheMap);
    cout << std::endl;

    // Insert key 4 which evicts the least recently used key.
    cout << "Fetching 3: " << cache.get(3) << endl;
    cache.print();
    printMap(cache.cacheMap);
    cout << std::endl;

    cache.put(4, 104);
    cache.print();
    printMap(cache.cacheMap);
    cout << std::endl;

    // Key 1 was evicted earlier, so this should return -1.
    cout << "Fetching 1: " << cache.get(1) << endl;
    cache.print();
    printMap(cache.cacheMap);
    cout << std::endl;

    // Key 3 remains in the cache and should be found.
    cout << "Fetching 3: " << cache.get(3) << endl;
    cache.print();
    printMap(cache.cacheMap);
    cout << std::endl;

    // Key 4 is the most recently inserted item and should still be available.
    cout << "Fetching 4: " << cache.get(4) << endl;
    cache.print();
    printMap(cache.cacheMap);
    cout << std::endl;

    return 0;
}
