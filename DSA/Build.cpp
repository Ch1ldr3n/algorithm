
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

inline int max(int a, int b) {
  if (a <= b)
    return b;
  else
    return a;
}

const int N = 1e6 + 10;  // 节点数最大值

int head[N], tail[N];  // 当前节点的孩子序列的头结点/尾结点的index
int child[N];          // 当前节点的孩子总数
int father[N];         // 当前节点的父节点的index
int height[N];         // 当前节点对应的子树的高度
int maxsuffh[N];       // 当前节点所有后缀的最大高度
int size[N];           // 当前节点对应的子树的规模
int nxt[N], pre[N];  // 当前节点的兄弟列表的前驱和后继节点的index
int n, m;            // 节点总数，操作数
int rankp[100010];  // 储存路径的所有rank;
int rankpp[100010];
// 多叉树的初始化
void init()  // right
{
  for (int i = 0; i <= n; ++i) {
    pre[i] = -1;
    nxt[i] = -1;
    father[i] = -1;
    head[i] = -1;
    tail[i] = -1;
  }
}

// 反向后序遍历计算size和height
void recurse(int id)  // nod
{
  size[id] = 1;
  // 如果当前是叶子节点
  if (child[id] == 0) {
    height[id] = 0;
    return;
  }

  int t = tail[id];
  while (t != -1) {
    recurse(t);
    size[id] += size[t];  //可能这里出错
    if (t == tail[id])
      maxsuffh[t] = height[t];
    else
      maxsuffh[t] = max(height[t], maxsuffh[nxt[t]]);
    t = pre[t];
  }
  height[id] = maxsuffh[head[id]] + 1;
}

// 读入多叉树的邻接表
void read()  // right
{
  scanf("%d%d", &n, &m);
  init();
  // 更新head,tail,pre,nxt,father,child
  for (int i = 1; i <= n; ++i) {
    int _child;  // 孩子个数
    scanf("%d", &_child);
    child[i] = _child;

    if (_child == 0)
      head[i] = tail[i] = -1;
    else {
      int last_id = -1;  // nod
      for (int j = 0; j < _child; ++j) {
        int id;
        scanf("%d", &id);
        if (head[i] == -1)
          head[i] = id;
        else
          nxt[last_id] = id;
        father[id] = i;
        pre[id] = last_id;
        last_id = id;
        // father[id] = i;
        // if (j == 0) head[i] = id;
        // else nxt[last_id] = id;
        // pre[id] = last_id;
        // last_id = id;
      }
      tail[i] = last_id;
    }
  }

  // 递归计算size,height,maxsuffh
  recurse(1);
}

// 根据路径长度和rank，找到该节点对应的index
int find(int length, int rank[]) {
  int index = 1;  // 初始化为根节点
  int r;          // 当前层的序数
  bool has_find = false;
  for (int i = 0; i < length; ++i) {
    r = rank[i];
    // rank不合法
    // if (has_find) continue;
    if (r >= child[index])
      break;
    else {
      index = head[index];  // target
      for (int j = 0; j < r; ++j) {
        index = nxt[index];
      }
    }
  }
  return index;
}

// 每次改变多叉树的结构之后，更新size
void update_size(int f, int changed)  // f->id->nod
{
  while (f != -1) {
    size[f] += changed;
    f = father[f];
  }
}

bool maxsuffh_change(int fa, int ch)  // fa->father, ch->child
{
  int fheight = height[fa];
  maxsuffh[ch] =
      max(height[ch], ch == tail[fa] ? height[ch] : maxsuffh[nxt[ch]]);
  ch = pre[ch];
  while (ch != -1) {
    maxsuffh[ch] =
        max(height[ch], ch == tail[fa] ? height[ch] : maxsuffh[nxt[ch]]);
    ch = pre[ch];
  }

  if (fheight != maxsuffh[head[fa]] + 1) {
    height[fa] = maxsuffh[head[fa]] + 1;
    return true;
  }
  return false;
}

void update_height(int id) {
  int f = father[id];  // father
  int c = id;          // child
  if (father[c] == -1) return;
  while (true) {
    if (!maxsuffh_change(f, c)) break;
    c = f;
    if (father[c] == -1) break;
    f = father[c];
  }
}

// 删除节点id对应的子树
void remove(int id)  // src
{
  int f = father[id];  // 父节点father
  int p = pre[id];     // 兄节点bro1
  int n = nxt[id];     // 弟节点bro2

  // 断开该子树与多叉树之间的连接
  // 如果id是中间结点
  if (p != -1 && n != -1) {
    nxt[p] = n;
    pre[n] = p;
  }
  // 如果id是兄弟序列中的头结点
  else if (p == -1 && n != -1) {
    head[f] = n;
    pre[n] = -1;
  }
  // 如果id是兄弟序列中的尾结点
  else if (p != -1 && n == -1) {
    tail[f] = p;
    nxt[p] = -1;
  }
  // 如果既是头结点也是尾结点（叶子节点）
  else
    head[f] = tail[f] = -1;

  // 更新父节点孩子个数
  child[f]--;

  int changed = size[id];
  update_size(f, -1 * changed);

  // 如果是仅有的孩子被删除
  if (child[f] == 0) {
    height[f] = 0;
    update_height(f);
    return;
  }

  int t = p;  // tem
  bool change = false;
  while (t != -1) {
    maxsuffh[t] = max(height[t], t == tail[f] ? height[t] : maxsuffh[nxt[t]]);
    t = pre[t];
  }
  if (height[f] != maxsuffh[head[f]] + 1) {
    height[f] = maxsuffh[head[f]] + 1;
    change = true;
  }
  if (change) update_height(f);
}

void add(int subtree, int to, int rank) {
  int f = to;  // father
  int p;       // bro1
  int n;       // bro2

  // 插在首位
  if (rank == 0) {
    // 原来父节点没有孩子
    if (child[f] == 0) {
      p = n = -1;
      head[f] = tail[f] = subtree;
      father[subtree] = f;
      pre[subtree] = nxt[subtree] = -1;
    } else {
      p = -1;
      n = head[f];
      pre[n] = subtree;
      pre[subtree] = -1;
      nxt[subtree] = n;
      father[subtree] = f;
      head[f] = subtree;
    }
  } else if (child[f] > 0 && rank == child[f]) {
    p = tail[f];
    n = -1;
    nxt[p] = subtree;
    pre[subtree] = p;
    nxt[subtree] = -1;
    father[subtree] = f;
    tail[f] = subtree;
  } else {
    int t = head[f];  // tem
    rank--;
    while (rank > 0) {
      t = nxt[t];
      rank--;
    }
    p = t;
    n = nxt[t];
    nxt[p] = subtree;
    if (n != -1) pre[n] = subtree;
    father[subtree] = f;
    nxt[subtree] = n;
    pre[subtree] = p;
  }

  child[f]++;

  int sizechange = size[subtree];
  update_size(f, sizechange);

  if (child[f] == 1) {
    height[f] = height[subtree] + 1;
    maxsuffh[subtree] = height[subtree];
    update_height(f);
    return;
  }

  int t = subtree;
  bool change = false;
  while (t != -1) {
    maxsuffh[t] = max(height[t], (t == tail[f]) ? height[t] : maxsuffh[nxt[t]]);
    t = pre[t];
  }
  if (height[f] != maxsuffh[head[f]] + 1) {
    height[f] = maxsuffh[head[f]] + 1;
    change = true;
  }
  if (change) update_height(f);
}

// 输入并执行操作
void run() {
  int flag;
  while (m--) {
    scanf("%d", &flag);
    if (flag == 0) {
      int slen, tlen, rank;
      scanf("%d", &slen);
      for (int i = 0; i < slen; ++i) scanf("%d", &rankp[i]);
      // int s = find(slen, rankp);
      // remove(s);
      scanf("%d", &tlen);
      for (int i = 0; i < tlen; ++i) scanf("%d", &rankpp[i]);
      scanf("%d", &rank);
      int s = find(slen, rankp);
      remove(s);
      int t = find(tlen, rankpp);
      add(s, t, rank);
    } else {
      int plen;  // 查询路径长度
      scanf("%d", &plen);
      for (int i = 0; i < plen; ++i) {
        scanf("%d", &rankp[i]);
      }
      int index = find(plen, rankp);
      if (flag == 1)
        printf("%d\n", height[index]);
      else if (flag == 2)
        printf("%d\n", size[index]);
    }
  }
}

int main() {
  read();
  // debug();
  run();
  return 0;
}