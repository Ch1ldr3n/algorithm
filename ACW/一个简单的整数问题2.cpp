#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
typedef long long LL;
int a[N];
int n, m;

struct Node {
  int l, r;
  LL add;
  LL sum;
} tr[N * 4];

void pushup(Node& u, Node& l, Node& r) { u.sum = l.sum + r.sum; }
void pushup(int u) { pushup(tr[u], tr[u << 1], tr[u << 1 | 1]); }

void pushdown(int u) {
  auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
  if (root.add) {
    left.add += root.add;
    left.sum += (LL)(left.r - left.l + 1) * root.add;
    right.add += root.add;
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
    tr[u].add += d;
    tr[u].sum += (LL)(tr[u].r - tr[u].l + 1) * d;
    return;
  }
  pushdown(u);
  int mid = tr[u].l + tr[u].r >> 1;
  if (l <= mid) modify(u << 1, l, r, d);
  if (r > mid) modify(u << 1 | 1, l, r, d);
  pushup(u);
}

LL query(int u, int l, int r) {
  if (tr[u].l >= l && tr[u].r <= r) {
    return tr[u].sum;
  }
  pushdown(u);
  int mid = tr[u].l + tr[u].r >> 1;
  LL sum = 0;
  if (l <= mid) sum = query(u << 1, l, r);
  if (r > mid) sum += query(u << 1 | 1, l, r);
  return sum;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  build(1, 1, n);
  char op[2];
  int l, r, d;
  while (m--) {
    scanf("%s%d%d", op, &l, &r);
    if (*op == 'C') {
      scanf("%d", &d);
      modify(1, l, r, d);
    } else
      printf("%lld\n", query(1, l, r));
  }
  return 0;
}