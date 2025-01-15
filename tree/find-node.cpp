#include "bst.h"
#include <cstdio>

using namespace std;



int main()
{

    BST<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(20);

    vector<int> result = tree.getInorder();
    printf("In order traversal: ");
    for (const int val: result)
    {
        printf("%4d", val);
    }
    printf("\n");

    vector<int> preorder = tree.getPreorder();
    printf("Pre order traversal: ");
    for (const int val: preorder)
    {
        printf("%4d", val);
    }
    printf("\n");

    vector<int> postorder = tree.getPostorder();
    printf("Post order traversal: ");
    for (const int val: postorder)
    {
        printf("%4d", val);
    }
    printf("\n");

    vector<int> levelOrder = tree.getLevelorder();
    printf("Level order traversal: ");
    for (const int val: levelOrder)
    {
        printf("%4d", val);
    }
    printf("\n");


    return (0);
}
