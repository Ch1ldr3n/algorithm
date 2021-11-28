// 144. 二叉树的前序遍历

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
        v.push_back(root->val);
        traverse(root->left, v);
        traverse(root->right, v);
    }

    void travPre_I1(TreeNode* root, vector<int>& v)
    {
        if (!root)
            return;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            auto x = s.top();
            s.pop();
            v.push_back(x->val);
            if (x->right)
                s.push(x->right);
            if (x->left)
                s.push(x->left);
        }
    }

    void visitAlongVine(TreeNode* root, vector<int>& v, stack<TreeNode*>& s)
    {
        while (root) { // 对空树情况也适用
            v.push_back(root->val);
            s.push(root->right); //右孩子(右子树)入栈(将来逆序出栈)
            root = root->left; //沿藤下行
        }
    }

    void travPre_I2(TreeNode* root, vector<int>& v)
    {
        stack<TreeNode*> s;
        // s.push(root);
        // while (!s.empty()) {
        //     auto x = s.top();
        //     s.pop();
        //     visitAlongVine(x, v, s);
        // }
        while (true) {
            visitAlongVine(root, v, s);
            if (s.empty())
                break;
            root = s.top();
            s.pop();
        }
    }

    vector<int>
    preorderTraversal(TreeNode* root)
    {
        vector<int> res;
        travPre_I2(root, res);
        return res;
    }
};
