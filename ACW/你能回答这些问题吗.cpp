#include <algorithm>
#include <cstdio>
using namespace std;

int n;                   //叶节点数
int m;                   //操作数
const int N = 5e5 + 10;  // n最大值
int w[N];                //叶节点初始数据
struct Node {
  int l, r;  //所维护的范围
  int sum;   //区间和
  int lmax;  //最大前缀和
  int rmax;  //最大后缀和
  int tmax;  //最大连续子段和
} tr[N * 4];

//用子节点更新父节点
void pushup(Node& u, Node& l, Node& r) {
  u.sum = l.sum + r.sum;
  u.lmax = max(l.lmax, l.sum + r.lmax);
  u.rmax = max(r.rmax, r.sum + l.rmax);
  u.tmax = max(max(l.tmax, r.tmax), l.rmax + r.lmax);
}

//重载
void pushup(int u) { pushup(tr[u], tr[u << 1], tr[u << 1 | 1]); }

//递归建树：tr[u]对应区间为[l,r]，维护[l,r]所有信息
void build(int u, int l, int r) {
  tr[u].l = l, tr[u].r = r;  //区间绑定
  //递归基：到达叶节点，此时直接填入数据
  if (l == r) {
    tr[u] = {l, r, w[l], w[l], w[l], w[l]};
    return;
  }
  //递归深入
  int mid = l + r >> 1;
  build(u << 1, l, mid);          //左儿子
  build(u << 1 | 1, mid + 1, r);  //右儿子
  //回溯：上面两条语句执行完之后，孩子节点都填完，据此填写当前节点数据
  pushup(u);
}

//修改叶节点。u根节点的编号，x叶节点序号，v修改值
void modify(int u, int x, int v) {
  //递归基：当前节点刚好维护的是所找的叶子节点
  if (tr[u].l == x && tr[u].r == x) {
    tr[u] = {x, x, v, v, v, v};
    return;
  }
  //每次选x在的那半边递归
  int mid = tr[u].l + tr[u].r >> 1;
  if (x <= mid)
    modify(u << 1, x, v);
  else
    modify(u << 1 | 1, x, v);
  pushup(u);
}

// 递归查询[l,r]：从[1,n]逐渐深入到[l,r]
Node query(int u, int l, int r) {
  if (l <= tr[u].l && tr[u].r <= r) return tr[u];
  int mid = tr[u].l + tr[u].r >> 1;
  // [Tl, mid] [mid+1, Tr]
  // [l, r]
  if (r <= mid)
    return query(u << 1, l, r);
  else if (l > mid)
    return query(u << 1 | 1, l, r);
  else {
    Node left = query(u << 1, l, r), right = query(u << 1 | 1, l, r);
    Node res;
    pushup(res, left, right);
    return res;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
  build(1, 1, n);
  int k, x, y;
  while (m--) {
    scanf("%d%d%d", &k, &x, &y);
    switch (k) {
      case 1:
        if (x > y) swap(x, y);
        printf("%d\n", query(1, x, y).tmax);
        break;
      case 2:
        modify(1, x, y);
        break;
      default:
        break;
    }
  }
  return 0;
}