/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void traverse(TreeNode* root, vector<int>& v)
    {
        if (!root)
            return;
        traverse(root->left, v);
        v.push_back(root->val);
        traverse(root->right, v);
    }

    vector<int> inorderTraversal(TreeNode* root)
    {
        vector<int> res;
        traverse(root, res);
        return res;
    }

    void goAlongVine(TreeNode* root, stack<TreeNode*>& s)
    {
        while (root) {
            s.push(x);
            x = x->left;
        }
    }

    void travIn(TreeNode* root, vector<int>& v)
    {
        stack<TreeNode*> s;
        while (true) {
            goAlongVine(root, s);
            if (s.empty())
                break;
            root = s.top();
            s.pop();
            v.emplace_back(root->val);
            root = root->right;
        }
    }
};