#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
int m;              //问题规模，线段树叶子节点数
int p;              // mod
const int N = 2e5;  // m最大值

struct Node {
  int l, r;  //线段树节点的范围
  int v;     //线段树对应的[Tl,Tr]区间的最大值
} tr[4 * N];

// 给tr[u]添加维护的范围，同时递归操作其子节点
void build(int u, int l, int r) {
  tr[u].l = l, tr[u].r = r;
  if (l == r) return;    //递归终点：已经深入到了叶子结点
  int mid = l + r >> 1;  //[l,mid] [mid+1,r]
  build(u << 1, l, mid);
  build(u << 1 | 1, mid + 1, r);
}

//用tr[u]的子节点属性更新tr[u]的属性，本题中为区间最大值
void pushup(int u) { tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v); }

//单点修改. u依然是根结点编号，x是要修改的数的序号也就是叶节点序号，v是新值
void modify(int u, int x, int v) {
  // 递归终点：当前tr[u]即是要修改的单点x
  if (tr[u].l == x && tr[u].r == x) {
    tr[u].v = v;
    return;
  }
  //未到终点，则深入递归
  int mid = tr[u].l + tr[u].r >> 1;
  //判断x在哪半边
  if (x <= mid)
    modify(u << 1, x, v);
  else
    modify(u << 1 | 1, x, v);
  pushup(u);
}

//查询[l, r]， 当前树节点tr[u]
int query(int u, int l, int r) {
  //递归终点：当前节点已经完全包含在查询区间里，不必再深入递归
  if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
  int mid = tr[u].l + tr[u].r >> 1;
  int maxv = 0;
  if (l <= mid) maxv = query(u << 1, l, r);
  if (r > mid) maxv = max(maxv, query(u << 1 | 1, l, r));
  return maxv;
}

int main() {
  scanf("%d%d", &m, &p);
  build(1, 1, m);
  int a = 0, n = 0;
  while (m--) {
    char op[2];
    int x;
    scanf("%s%d", op, &x);
    if (op[0] == 'Q') {  // query
      a = query(1, n - x + 1, n);
      printf("%d\n", a);
    } else {  // modify
      n++;
      modify(1, n, ((LL)x + a) % p);  //防止int溢出
    }
  }
  return 0;
}