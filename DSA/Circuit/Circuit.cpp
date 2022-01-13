#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 500000 + 10;
const int maxm = 32 * maxn;
typedef unsigned long long ull;
ull a[maxn];
int n, k;

// trie树
int son[maxm][2], idx;

// 存储叶子结点
int leaf[maxn], idx_leaf;

// 存储队列
int nxt[maxn];
int val[maxn];  // 存储这个01串对应的下标
int idxq;

// val: 01串， id: 对应的下标（0～n-1）
void insert(ull num, int id) {
  int p = 0;
  for (int i = 63; i >= 0; i--) {
    int u = (num >> i) & 1;
    //如果对应的儿子没创建
    if (!son[p][u]) {
      if (i != 0)
        son[p][u] = ++idx;  //中间节点
      else {
        son[p][u] = idx_leaf;
        leaf[idx_leaf++] = -1;
      }  //叶子结点，从0开始
    }
    // 如果对应的儿子已经创建但是被删除
    else if (son[p][u] < 0) {
      son[p][u] = -son[p][u];
    }
    p = son[p][u];
  }
  // 此时p是叶子结点，如果对应队列为空
  if (leaf[p] == -1) {
    val[idxq] = id;
    nxt[idxq] = -1;
    leaf[p] = idxq++;
  } else {  //加到队尾
    int t = leaf[p];
    while (nxt[t] != -1) t = nxt[t];
    val[idxq] = id;
    nxt[idxq] = -1;
    nxt[t] = idxq++;
  }
}

int path[64];
void del(ull val) {
  int p = 0;
  memset(path, 0, sizeof(path));
  for (int i = 63; i >= 0; i--) {
    int u = (val >> i) & 1;
    path[63 - i] = p;
    p = son[p][u];
  }
  leaf[p] = nxt[leaf[p]];  //将第一个记录移出去
  //如果删除之后，队列为空，则需要将路径移除
  if (leaf[p] == -1) {
    for (int i = 63; i >= 1; i--) {
      int kbit = (val >> (63 - i)) & 1;
      int pbit = (val >> (64 - i)) & 1;
      if (i == 63) {
        if (son[path[i]][!kbit] <= 0 || leaf[son[path[i]][!kbit]] == -1)
          son[path[i - 1]][pbit] = -son[path[i - 1]][pbit];
        else
          break;
      } else {
        if (son[path[i]][!kbit] <= 0)
          son[path[i - 1]][pbit] = -son[path[i - 1]][pbit];
        else
          break;
      }
    }
  }
}

int query(ull num, int id) {
  int p = 0;
  for (int i = 63; i >= 0; --i) {
    int u = (num >> i) & 1;
    int k = son[p][!u];  // 最优路径
    if (i != 0) {        //不是叶结点
      if (k > 0) {
        p = k;
      } else {
        p = son[p][u];
      }
    } else {
      if (k > 0 && leaf[k] != -1)
        p = son[p][!u];
      else
        p = son[p][u];
    }
  }
  int res = leaf[p];
  if (val[leaf[p]] == id) res = nxt[res];
  return val[res];
}

inline ull getUllFromStr(char str[]) {
  ull ans = 0;
  for (int i = 0; i < 64; ++i) {
    ans *= 2;
    ans += str[i] - '0';
  }
  return ans;
}

int main() {
  //初始化 读入数据
  int n, k;
  scanf("%d %d", &n, &k);
  char ch[66];
  for (int i = 0; i < n; ++i) {
    scanf("%s", ch);
    a[i] = getUllFromStr(ch);
  }
  idx = 1;
  for (int i = 0; i < n; ++i) {
    // 此时对编号为i的元件找最大的异或对
    // 先构建好对应的trie树
    // [i-k-1,i+k+1] 交 [0, n-1]
    // 初始[0, k+1],

    int L, R;           // 维护当前的理想范围
    int l = 0, r = -1;  // 维护当前实际加入trie树中的范围[l,r]
    for (int i = 0; i < n; ++i) {
      L = i - k - 1;
      R = i + k + 1;
      while (r < R && r < n - 1) insert(a[++r], r);
      while (l < L) del(a[l++]);
      printf("%d\n", query(a[i], i));
    }
    return 0;
  }
}
