#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;  // 二维向量存储答案
    //判断特殊情况：树为空
    if (!root) return res;
    //创建辅助队列，经典bfs
    queue<TreeNode*> q;
    //树根入队
    q.push(root);
    /*
     * 每轮迭代，q中为当前层所有的节点
     * 将这些节点都放在res的最后一行中，这些节点的后继都入队（不变性）
     * 当前层所有节点都没有后继了，迭代结束
     */
    while (!q.empty()) {
      res.push_back(vector<int>());  // res新增一行来存当前层的节点
      int curLevelSize = q.size();   //当前层的节点数
      for (int i = 0; i < curLevelSize; i++) {
        auto node = q.front();
        q.pop();
        res.back().push_back(node->val);  // back() 取向量最后一个元素
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
      }
    }
    return res;
  }
};