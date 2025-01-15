#ifndef BST_H
#define BST_H

#include <queue>
#include <stack>
#include <vector>
using namespace std;

template <class T> class TreeNode
{
    private:
    T         data;
    TreeNode* left;
    TreeNode* right;

    public:
    TreeNode(T d) : data(d), left(nullptr), right(nullptr)
    {
    }

    inline T getData() const
    {
        return data;
    }

    inline TreeNode* getLeft() const
    {
        return left;
    }

    inline TreeNode* getRight() const
    {
        return right;
    }

    inline void setData(T d)
    {
        data = d;
    }

    inline void setLeft(TreeNode* l)
    {
        left = l;
    }

    inline void setRight(TreeNode* r)
    {
        right = r;
    }
};

template <class T> class BST
{
    private:
    TreeNode<T>* root;

    public:
    BST() : root(nullptr) {};
    ~BST();

    void inorderTraversal();

    TreeNode<T>* insert(T data);

    vector<T> getInorder();
    vector<T> getPreorder();
    vector<T> getPostorder();
    vector<T> getLevelorder();
};

template <typename T> void BST<T>::inorderTraversal()
{
    if (nullptr == root)
    {
        return;
    }

    stack<TreeNode<T>*> nodeStack;
    TreeNode<T>*        current = root;

    while ((nullptr != current) || (false == nodeStack.empty()))
    {
        while (nullptr != current)
        {
            nodeStack.push(current);
            current = current->getLeft();
        }

        current = nodeStack.top();
        nodeStack.pop();

        printf("%4d", current->getData());
        current = current->getRight();
    }

    printf("\n");
}

template <typename T> TreeNode<T>* BST<T>::insert(T data)
{
    TreeNode<T>* newNode = new TreeNode<T>(data);

    if (nullptr == root)
    {
        root = newNode;
    }
    else
    {
        TreeNode<T>* node   = root;
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

template <typename T> BST<T>::~BST()
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
            TreeNode<T>* predecessor = node->getLeft();
            while (nullptr != predecessor->getRight())
            {
                predecessor = predecessor->getRight();
            }

            /* Found predecessor
             * Delete current node and link predeceessor with the right subtree
             */
            predecessor->setRight(node->getRight());
            node = node->getLeft();
            delete temp;
        }
    }
}

template <typename T> vector<T> BST<T>::getInorder()
{
    vector<T> result;

    TreeNode<T>* current = root;
    while (nullptr != current)
    {
        if (nullptr == current->getLeft())
        {
            /* Left node does not exists */
            result.push_back(current->getData());
            current = current->getRight();
        }
        else
        {
            /* Find the inorder predecessor and link its right to current node
             * The right node of predecessor will be nullptr (as it is leaf node)
             * as setting the right of predecessor to current node, check for loop
             */
            TreeNode<T>* predecessor = current->getLeft();
            while ((nullptr != predecessor->getRight()) && (current != predecessor->getRight()))
            {
                predecessor = predecessor->getRight();
            }

            /* Found the predecessor */
            if (nullptr == predecessor->getRight())
            {
                /* Establish the link to current node and recurse on left subtree */
                predecessor->setRight(current);
                current = current->getLeft();
            }
            else
            {
                /* the right link points to the successor of left sub tree
                 * move to successor and delete the link
                 */
                result.push_back(current->getData());
                current = current->getRight();
                predecessor->setRight(nullptr);
            }
        }
    }

    return result;
}

template <typename T> vector<T> BST<T>::getPreorder()
{
    vector<T> result;

    TreeNode<T>* node = root;
    while (nullptr != node)
    {
        if (nullptr == node->getLeft())
        {
            /* Left node does not exists */
            result.push_back(node->getData());
            node = node->getRight();
        }
        else
        {
            TreeNode<T>* predecessor = node->getLeft();

            while ((nullptr != predecessor->getRight()) && (node != predecessor->getRight()))
            {
                predecessor = predecessor->getRight();
            }

            /* Found the in-order  predecessor */
            if (nullptr == predecessor->getRight())
            {
                /* Establish the link to current node and recurse on left subtree */
                result.push_back(node->getData());
                predecessor->setRight(node);
                node = node->getLeft();
            }
            else
            {
                /* the right link points to the successor of left sub tree
                 * move to successor and delete the link
                 */
                node = node->getRight();
                predecessor->setRight(nullptr);
            }
        }
    }

    return result;
}

template <typename T> vector<T> BST<T>::getPostorder()
{
    vector<T> result;

    size_t size = result.size();

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

            /* Successor found, link it to current node */
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

    /* Reverse vector */
    reverse(result.begin(), result.end());
    return result;
}

template <typename T> vector<T> BST<T>::getLevelorder()
{
    if (nullptr == root)
    {
        return vector<T>();
    }

    vector<T>           result;
    queue<TreeNode<T>*> q;
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

    return result;
}

#endif // !BST_H
