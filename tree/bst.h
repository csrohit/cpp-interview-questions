#ifndef _BST_H_
#define _BST_H_

#include <queue>
#include <stack>
#include <vector>

#include "binarytree.h"

template <class T> class BST : public BinaryTree<T>
{
    public:
    TreeNode<T>* insert(T data)
    {
        TreeNode<T>* newNode = new TreeNode<T>(data);

        if (nullptr == this->root)
        {
            this->root = newNode;
        }
        else
        {
            TreeNode<T>* node   = this->root;
            TreeNode<T>* parent = nullptr;

            while (nullptr != node)
            {
                if (data < node->getData())
                {
                    if (nullptr != node->getLeft())
                    {
                        node = node->getLeft();
                    }
                    else
                    {
                        node->setLeft(newNode);
                        break;
                    }
                }
                else if (data > node->getData())
                {
                    if (nullptr != node->getRight())
                    {
                        node = node->getRight();
                    }
                    else
                    {
                        node->setRight(newNode);
                        break;
                    }
                }
                else
                {
                    // data already exists
                }
            }
        }
        return newNode;
    }

    void remove(const T d)
    {
        if (nullptr == this->root)
        {
            return;
        }

        TreeNode<T>* node   = this->root;
        TreeNode<T>* parent = nullptr;
        while ((nullptr != node) && (d != node->getData()))
        {
            parent = node;
            if (d > node->getData())
            {
                node = node->getRight();
            }
            else
            {
                node = node->getLeft();
            }
        }

        if (nullptr == node)
        {
            /* Node not found */
            return;
        }
        else if ((nullptr != node->getLeft()) && (nullptr != node->getRight()))
        {
            /* Node with both children */
            /* Replace current node with inorder successor */
            TreeNode<T>* successor       = node->getRight();
            TreeNode<T>* successorParent = node;

            while (nullptr != successor->getLeft())
            {
                successorParent = successor;
                successor       = successor->getLeft();
            }

            node->setData(successor->getData());

            /* Current node has been replaced with successor node and now there are 2 nodes with successor data
             * Hence we need to remove the successor node.
             * But the left subtree of successor node is null, we can continue to next steps assuming
             * successor node was the original node to be removed
             */

            parent = successorParent;
            node   = successor;
        }

        TreeNode<T>* child = (nullptr != node->getLeft()) ? node->getLeft() : node->getRight();

        /* Remove root node */
        if (nullptr == parent)
        {
            this->root = child;
        }
        else if (parent->getLeft() == node)
        {
            parent->setLeft(child);
        }
        else
        {
            parent->setRight(child);
        }
        delete node;
    }
};

#endif //_BST_H_
