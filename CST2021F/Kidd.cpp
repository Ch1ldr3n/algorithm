#include <cstdio>
#include <cstring>
using namespace std;
#define int_max 2147483647
typedef long long LL;
int n;                   // 序列总长度。本题其实是幌子。
int m;                   // 操作数。对应m个区间，2m个端点
const int M = 2e5 + 10;  // m的最大值， 离散化总点数最大为2M
struct Util {
  char op;
  int l, r;
} qh[M];  // 存储操作序列，以便最后统一执行

struct Node {
  int l, r;
  LL add;  // 懒标记
  LL sum;  // 区间和
} tr[M << 3];

LL alls[2 * M];
int idx;  //存储所有待离散化的值

inline void swap(LL &a, LL &b) {
  LL t = a;
  a = b;
  b = t;
}

// 离散化前->离散化后
inline int find(int x) {
  int l = 1, r = idx;
  while (l < r) {
    int mid = l + r >> 1;
    if (alls[mid] >= x)
      r = mid;
    else
      l = mid + 1;
  }
  return r;
}

void quickSort(LL q[], int l, int r) {
  if (l >= r) return;
  LL x = q[l + r >> 1], i = l - 1, j = r + 1;
  while (i < j) {
    do i++;
    while (q[i] < x);
    do j--;
    while (q[j] > x);
    if (i < j) swap(q[i], q[j]);
  }
  quickSort(q, l, j), quickSort(q, j + 1, r);
}

void uniquify(LL q[], int l, int &r) {
  int i = l, j = l;
  while (++j <= r) {
    if (q[j] != q[i]) q[++i] = q[j];
  }
  r = i;
}

// [1, idx]建树
void build(int u, int l, int r) {
  tr[u].l = l, tr[u].r = r;
  if (l == r) {
    tr[u] = {l, r, 0, 0};
    return;
  }
  int mid = l + r >> 1;
  build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void pushup(int u) { tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum; }

void pushdown(int u) {
  auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
  if (root.add) {
    left.add += root.add;
    left.sum += (LL)(alls[left.r + 1] - alls[left.l]) * root.add;
    right.add += root.add;
    right.sum += (LL)(alls[right.r + 1] - alls[right.l]) * root.add;
    root.add = 0;
  }
}
//如何根据节点编号
void modify(int u, int l, int r) {
  if (l <= tr[u].l && tr[u].r <= r) {
    tr[u].sum += alls[tr[u].r + 1] - alls[tr[u].l];
    tr[u].add += 1;
    return;
  }
  pushdown(u);
  int mid = tr[u].l + tr[u].r >> 1;
  if (l <= mid) modify(u << 1, l, r);
  if (r > mid) modify(u << 1 | 1, l, r);
  pushup(u);
}

LL query(int u, int l, int r) {
  if (l <= tr[u].l && tr[u].r <= r) {
    return tr[u].sum;
  }
  pushdown(u);
  int mid = tr[u].l + tr[u].r >> 1;
  LL res = 0;
  if (l <= mid) res += query(u << 1, l, r);
  if (r > mid) res += query(u << 1 | 1, l, r);
  return res;
}

void show_1() {
  for (int i = 1; i <= idx; ++i) printf("%lld ", alls[i]);
  printf(" %lld\n", alls[idx + 1]);
}

void show_2() {
  for (int i = 1; i <= 20; ++i) {
    printf("%d %d\n", tr[i].l, tr[i].r);
  }
}

int main() {
  //   freopen("input.txt", "r", stdin);
  scanf("%d%d", &n, &m);

  // m次操作，一共涉及到2m个点。对这些点做离散化处理
  char op[2];
  int l, r;
  for (int i = 0; i < m; ++i) {
    scanf("%s%d%d", op, &l, &r);
    qh[i] = {op[0], l, r};
    alls[++idx] = l;
    alls[++idx] = r;
    alls[++idx] = (LL)l + 1;
    alls[++idx] = (LL)r + 1;
  }

  //离散化
  // 排序
  quickSort(alls, 1, idx);
  // 去重
  uniquify(alls, 1, idx);
  // alls[1, idx]
  //添加分割点
  idx--;
  //   for (int i = 1, oldSize = idx; i < oldSize; ++i) {
  //     if (alls[i + 1] - alls[i] > 1) alls[++idx] = alls[i] + 1;
  //   }

  //   quickSort(alls, 1, idx);
  //   return 0;
  //   alls[idx + 1] = alls[idx] + 1;  // 最后一位
  //   while (1)
  ;
  //   show_1();
  //   while (1)
  // 建树
  ;  //   return 0;
  build(1, 1, idx);
  //   show_2();
  for (int i = 0; i < m; ++i) {
    l = qh[i].l;
    r = qh[i].r;
    if (qh[i].op == 'Q') {
      printf("%lld\n", query(1, find(l), find(r)));
    } else {
      modify(1, find(l), find(r));
    }
  }
  return 0;
}
