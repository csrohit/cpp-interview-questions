#ifndef _BINARY_TREE_
#define _BINARY_TREE_


#include <vector>
#include <queue>
#include "TreeNode.h"

template <typename T> class BinaryTree
{
    public:
    TreeNode<T>* root;

    BinaryTree() : root(nullptr) {};

    ~BinaryTree()
    {
        TreeNode<T>* node = root;

        while (nullptr != node)
        {
            TreeNode<T>* temp = node;
            if (nullptr == node->getLeft())
            {
                node = node->getRight();
                delete temp;
            }
            else
            {
                /* Find inorder predecessor */
                TreeNode<T>* predecessor = node->getLeft();

                while (nullptr != predecessor->getRight())
                {
                    predecessor = predecessor->getRight();
                }

                /* Link right subtree of node to post order predecessor of node */
                predecessor->setRight(node->getRight());
                node = node->getLeft();
                delete temp;
            }
        }
    }

    void getInorder(std::vector<T>& result) const
    {
        TreeNode<T>* node = root;

        while (nullptr != node)
        {
            if (nullptr == node->getLeft())
            {
                result.push_back(node->getData());
                node = node->getRight();
            }
            else
            {
                /* Get inorder predecessor to root node */
                TreeNode<T>* predecessor = node->getLeft();

                while ((nullptr != predecessor->getRight()) && (node != predecessor->getRight()))
                {
                    predecessor = predecessor->getRight();
                }

                /* If right sub tree is null then set root node as right subtree */
                if (nullptr == predecessor->getRight())
                {
                    predecessor->setRight(node);
                    node = node->getLeft();
                }
                else
                {
                    /* Remove root node as right sub tree */
                    result.push_back(node->getData());
                    predecessor->setRight(nullptr);
                    node = node->getRight();
                }
            }
        }
    }

    void getPreorder(std::vector<T>& result) const
    {
        TreeNode<T>* node = root;

        while (nullptr != node)
        {
            if (nullptr == node->getLeft())
            {
                result.push_back(node->getData());
                node = node->getRight();
            }
            else
            {
                /* Find rightmost node of left sub tree */
                TreeNode<T>* predecessor = node->getLeft();

                while ((nullptr != predecessor->getRight()) && (node != predecessor->getRight()))
                {
                    predecessor = predecessor->getRight();
                }

                if (nullptr == predecessor->getRight())
                {
                    result.push_back(node->getData());
                    predecessor->setRight(node);
                    node = node->getLeft();
                }
                else
                {
                    predecessor->setRight(nullptr);
                    node = node->getRight();
                }
            }
        }
    }

    void getPostorder(std::vector<T>& result) const
    {
        TreeNode<T>* node = root;

        while (nullptr != node)
        {
            if (nullptr == node->getRight())
            {
                result.push_back(node->getData());
                node = node->getLeft();
            }
            else
            {
                /* Find inorder successor */
                TreeNode<T>* successor = node->getRight();

                while ((nullptr != successor->getLeft()) && (node != successor->getLeft()))
                {
                    successor = successor->getLeft();
                }

                if (nullptr == successor->getLeft())
                {
                    result.push_back(node->getData());
                    successor->setLeft(node);
                    node = node->getRight();
                }
                else
                {
                    successor->setLeft(nullptr);
                    node = node->getLeft();
                }
            }
        }
        reverse(result.begin(), result.end());
    }

    void getLevelorder(std::vector<T>& result) const
    {
        if (nullptr == root)
        {
            return;
        }

        std::queue<TreeNode<T>*> q;
        q.push(root);
        while (false == q.empty())
        {
            TreeNode<T>* node = q.front();
            result.push_back(node->getData());
            q.pop();

            if (nullptr != node->getLeft())
            {
                q.push(node->getLeft());
            }

            if (nullptr != node->getRight())
            {
                q.push(node->getRight());
            }
        }
    }
};
#endif // !_BINARY_TREE_
