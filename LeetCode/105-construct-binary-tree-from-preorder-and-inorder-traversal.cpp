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

/*
    preorder = [3,9,20,15,7]
    inorder = [9,3,15,20,7]
    1. root -> 3
    分而治之
    2. inorder -> [9], [15,20,7] (查找)
    3. preorder -> [9], [20,15,7]
    4. 递归处理子问题 ([9],[9]), ([20,15,7], [15,20,7])
*/

class Solution {
 public:
  unordered_map<int, int> getPos;
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    for (int i = 0; i < inorder.size(); ++i) getPos[inorder[i]] = i;
    return build(preorder, inorder, 0, preorder.size() - 1, 0,
                 inorder.size() - 1);
  }
  // 由preorder[pl,pr] 和 inorder[il,ir] 递归构造二叉树
  TreeNode* build(vector<int>& preorder, vector<int>& inorder, int pl, int pr,
                  int il, int ir) {
    // 递归终点：序列为空
    if (pl > pr) return NULL;
    // 构造根
    int rootVal = preorder[pl];
    auto root = new TreeNode(rootVal);
    // 分而治之
    int div = getPos[rootVal];
    // pre: [pl | pl+1, ..., ? | ? + 1, ..., pr]
    // in: [il, ..., div-1 | div | div+1, ...,ir]
    // ? - pl - 1 = div - 1 - il
    root->left = build(preorder, inorder, pl + 1, div - il + pl, il, div - 1);
    root->right = build(preorder, inorder, div - il + pl + 1, pr, div + 1, ir);
    return root;
  }
};