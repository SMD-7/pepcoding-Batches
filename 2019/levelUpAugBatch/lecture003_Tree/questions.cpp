#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *a = nullptr, *b = nullptr, *prev_ = nullptr;
bool recoverTree_(TreeNode *root)
{
    if (root == nullptr)
        return false;

    if (recoverTree_(root->left))
        return true;

    if (prev_ != nullptr && prev_->val > root->val)
    {
        b = root;
        if (a == nullptr)
            a = prev_;
        else
            return true;
    }

    prev_ = root;
    if (recoverTree_(root->right))
        return true;
    return false;
}

void recoverTree(TreeNode *root)
{
    recoverTree_(root);
    if (a != nullptr)
    {
        int temp = a->val;
        a->val = b->val;
        b->val = temp;
    }
}

//510
Node *inorderSuccessor(Node *node)
{

    Node *curr = node;
    Node *succ = nullptr;
    if (node->right != nullptr)
    {
        succ = curr->right;
        while (succ->left != nullptr)
        {
            succ = succ->left;
        }

        return succ;
    }

    while (curr->parent != nullptr && curr->parent->val < node->val)
    {
        curr = curr->parent;
    }

    return curr->parent != nullptr ? curr->parent : nullptr;
}

Node *inorderSuccessor(Node *node)
{

    Node *curr = node;
    Node *succ = nullptr;
    if (node->right != nullptr)
    {
        succ = curr->right;
        while (succ->left != nullptr)
        {
            succ = succ->left;
        }

        return succ;
    }

    while (curr->parent != nullptr)
    {
        if (curr->parent->left == curr)
            return curr->parent;
        curr = curr->parent;
    }

    return nullptr;
}

//235
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{

    TreeNode *curr = root;
    while (curr != nullptr)
    {
        if (curr->val < p->val && curr->val < q->val)
            curr = curr->right;
        else if (curr->val > p->val && curr->val > q->val)
            curr = curr->left;
        else
            break;
    }

    return curr;
}


//Leetcode 173
class BSTIterator
{
public:
    stack<TreeNode *> st;
    BSTIterator(TreeNode *root)
    {
        allLeft(root);
    }

    void allLeft(TreeNode *node)
    {
        while (node != nullptr)
        {
            st.push(node);
            node = node->left;
        }
    }

    int next()
    {
        TreeNode *node = st.top();
        st.pop();
        allLeft(node->right);

        return node->val;
    }

    bool hasNext()
    {
        return st.size() != 0;
    }