/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode *father;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL), father(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* p)
    {
        if (!p)
            return NULL;
        if (p->right) {
            auto q = p->right;
            while (q->left) {
                q = q->left;
            }
            return q;
        } else {
            while (p->father && p->father->right == p) {
                p = p->father;
            }
            return p->father;
        }
    }
};