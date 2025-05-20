#include "bst.h"
#include <cstdio>
#include "binarytree.h"

using namespace std;


int main()
{

    BST<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(3);
    tree.insert(4);
    tree.insert(1);
    tree.insert(7);
    tree.insert(25);
    tree.insert(15);
    tree.insert(21);
    tree.insert(42);
    tree.insert(22);


    tree.remove(20);
    // BinaryTree<int> tree;
    // tree.root = new TreeNode(10);
    // tree.root->setLeft(new TreeNode(5));
    // tree.root->getLeft()->setLeft(new TreeNode(3));
    // tree.root->getLeft()->getLeft()->setLeft(new TreeNode(1));
    // tree.root->getLeft()->getLeft()->setRight(new TreeNode(4));
    // tree.root->getLeft()->setRight(new TreeNode(7));
    // tree.root->setRight(new TreeNode(20));
    // tree.root->getRight()->setRight(new TreeNode(22));
    // tree.root->getRight()->getRight()->setLeft(new TreeNode(21));
    // tree.root->getRight()->setLeft(new TreeNode(15));

    vector<int> result;
    tree.getInorder(result);
    printf("In order traversal: ");
    for (const int val: result)
    {
        printf("%4d", val);
    }
    printf("\n");

    result.clear();
    tree.getPreorder(result);
    printf("Pre order traversal: ");
    for (const int val: result)
    {
        printf("%4d", val);
    }
    printf("\n");

    result.clear();
    tree.getPostorder(result);
    printf("Post order traversal: ");
    for (const int val: result)
    {
        printf("%4d", val);
    }
    printf("\n");

    result.clear();
    tree.getLevelorder(result);
    printf("Level order traversal: ");
    for (const int val: result)
    {
        printf("%4d", val);
    }
    printf("\n");

    // vector<int> levelOrder = tree.getLevelorder();
    // printf("Level order traversal: ");
    // for (const int val: levelOrder)
    // {
    //     printf("%4d", val);
    // }
    // printf("\n");


    return (0);
}
