#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long LL;
const int N = 1e5 + 10;
int n, m;
int a[N];
const int M = 2e5 + 10;
LL alls[2 * M];
struct Node {
  int l, r;
  LL add, sum;
} tr[4 * N];

void pushup(int u) { tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum; }

void pushdown(int u) {
  auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
  if (root.add) {
    left.add += root.add;
    right.add += root.add;
    left.sum += (LL)(left.r - left.l + 1) * root.add;
    right.sum += (LL)(right.r - right.l + 1) * root.add;
    root.add = 0;
  }
}

void build(int u, int l, int r) {
  tr[u].l = l, tr[u].r = r;
  if (l == r) {
    tr[u] = {l, r, 0, a[l]};
    return;
  }
  int mid = l + r >> 1;
  build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
  pushup(u);
}

void modify(int u, int l, int r, int d) {
  if (l <= tr[u].l && tr[u].r <= r) {
    tr[u].sum += (LL)(tr[u].r - tr[u].l + 1) * d;
    tr[u].add += d;
    return;
  }
  pushdown(u);
  int mid = tr[u].l + tr[u].r >> 1;
  if (l <= mid) modify(u << 1, l, r, d);
  if (r > mid) modify(u << 1 | 1, l, r, d);
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

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  build(1, 1, n);
  char op[2];
  int l, r, d;
  while (m--) {
    scanf("%s%d%d", op, &l, &r);
    if (op[0] == 'C') {
      scanf("%d", &d);
      modify(1, l, r, d);
    } else {
      printf("%lld\n", query(1, l, r));
    }
  }
  return 0;
}