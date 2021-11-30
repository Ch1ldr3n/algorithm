#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;
// Why long long? 10^18
int n;                   // size
int m;                   // op num
const int N = 5e5 + 10;  // max n
LL a[N];                 // raw data
// assume there is b[N], b[i] = a[i] - a[i-1];
// so that a[i] = b[i]+...+b[1] (+ a[0] which == 0)

// greatest common divisor
LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

struct Node {
  int l, r;  // node range (in array b)
  LL sum;    // range sum: b[l]+...+b[r]
  LL d;      // gcd(b[l],...,b[r])
             // why not a? hard to maintain,
             // should be divided into two parts
             // gcd(a[l], ..., a[r])
             // = gcd(a[l], a[l+1]-a[l], ..., a[r]-a[r-1])
             // = gcd(a[l],b[l+1],...,b[r])
             // 注意当l==r时，两部分只剩下一部分了。
} tr[4 * N];

void pushup(Node& u, Node& l, Node& r) {
  u.sum = l.sum + r.sum;
  u.d = gcd(l.d, r.d);
}
void pushup(int u) { pushup(tr[u], tr[u << 1], tr[u << 1 | 1]); }

void build(int u, int l, int r) {
  // 区间绑定
  tr[u].l = l, tr[u].r = r;
  // 递归基：叶子结点
  if (l == r) {
    LL b = a[r] - a[r - 1];
    tr[u] = {l, r, b, b};  // 叶子结点（单点）的d和sum都等于自己的值
    return;
  }
  //分而治之
  int mid = l + r >> 1;
  build(u << 1, l, mid);
  build(u << 1 | 1, mid + 1, r);
  pushup(u);
}

void modify(int u, int x, LL v) {
  //递归基
  if (tr[u].l == x && tr[u].r == x) {
    auto newv = tr[u].sum + v;
    tr[u] = {x, x, newv, newv};
    return;
  }
  int mid = tr[u].l + tr[u].r >> 1;
  if (x <= mid)
    modify(u << 1, x, v);
  else
    modify(u << 1 | 1, x, v);
  pushup(u);
}

Node query(int u, int l, int r) {
  // 这里因为后面查询的区间实际长度可能为1，所以l可能>r
  if (l > r) return {0};
  if (l <= tr[u].l && tr[u].r <= r) return tr[u];
  int mid = tr[u].l + tr[u].r >> 1;
  // [tr[u].l, mid]  [mid+1, tr[u].r]
  // [l, r]
  if (r <= mid)
    return query(u << 1, l, r);
  else if (l > mid)
    return query(u << 1 | 1, l, r);
  else {
    auto left = query(u << 1, l, r);
    auto right = query(u << 1 | 1, l, r);
    Node res;
    pushup(res, left, right);
    return res;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
  build(1, 1, n);
  char op[2];
  int l, r;
  LL d;
  while (m--) {
    scanf("%s", op);
    if (op[0] == 'C') {
      scanf("%d%d%lld", &l, &r, &d);
      // 把a[l],...,a[r]都加上d，相当于
      // b[l]+=d,b[r+1]-=d
      modify(1, l, d);
      if (r + 1 <= n) modify(1, r + 1, -d);
    } else {
      scanf("%d%d", &l, &r);
      auto left = query(1, 1, l).sum, right = query(1, l + 1, r).d;
      printf("%lld\n", abs(gcd(left, right)));
    }
  }
  return 0;
}
