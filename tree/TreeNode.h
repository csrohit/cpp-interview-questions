#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

template <typename T> class TreeNode
{
    private:
    T         data;
    TreeNode* left;
    TreeNode* right;

    public:
    TreeNode(T d) : data(d), left(nullptr), right(nullptr) {};

    T getData() const
    {
        return data;
    }

    TreeNode* getLeft() const
    {
        return left;
    }

    TreeNode* getRight() const
    {
        return right;
    }

    void setRight(TreeNode* const node)
    {
        right = node;
    }

    void setLeft(TreeNode* const node)
    {
        left = node;
    }

    void setData(const T d)
    {
        data = d;
    }
};

#endif // _TREE_NODE_H_
