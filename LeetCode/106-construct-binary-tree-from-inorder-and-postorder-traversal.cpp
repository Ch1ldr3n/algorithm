/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
 public:
  unordered_map<int, int> getPos;
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    for (int i = 0; i < inorder.size(); ++i) getPos[inorder[i]] = i;
    return build(inorder, postorder, 0, inorder.size() - 1, 0,
                 postorder.size() - 1);
  }
  TreeNode* build(vector<int>& inorder, vector<int>& postorder, int il, int ir,
                  int pl, int pr) {
    if (il > ir) return NULL;
    int rootVal = postorder[pr];
    auto root = new TreeNode(rootVal);
    int div = getPos[rootVal];
    // in: [il, div-1 | div | div+1, ir]
    // post: [pl, ? | ?+1, pr-1 | pr]
    // ? - pl = div - 1 - il
    root->left = build(inorder, postorder, il, div - 1, pl, div - 1 - il + pl);
    root->right = build(inorder, postorder, div + 1, ir, pl + div - il, pr - 1);
    return root;
  }
};