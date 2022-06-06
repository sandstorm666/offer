//给定一个二叉树的根节点root，返回它的中序遍历。

#include <vector>
using namespace std;
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
//中序遍历就是先输出左结点的值，再输出本节点的值，最后输出右节点的值
class Solution
{
public:
    vector<int> v;
    void middle(TreeNode *root)
    {
        if (!root)
            return;
        if (root->left)
            middle(root->left);
        //只需要插入一次值，因为每个结点都会进入一次递归函数
        v.push_back(root->val);//递归函数后插入,这样会在递归函数返回最上层后，最上层先插入，最内层最后插入
        if (root->right)
            middle(root->right);
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        middle(root);
        return v;
    }
};