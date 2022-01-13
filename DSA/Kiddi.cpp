#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 1000010;
const int M = 2e5 + 3;

char op[M][2];
int point[2 * M];
int arr[2 * M];

int n, m;
struct Node {
  int l, r;
  LL sum, add;
} tr[N * 4];

void quick_sort(int q[], int l, int r) {
  if (l >= r) return;
  int i = l - 1, j = r + 1, x = q[l + r >> 1];
  while (i < j) {
    do i++;
    while (q[i] < x);
    do j--;
    while (q[j] > x);
    if (i < j) {
      int t = q[i];
      q[i] = q[j];
      q[j] = t;
    }
  }
  quick_sort(q, l, j);
  quick_sort(q, j + 1, r);
}
    
void pushup(int u) { tr[u].sum = tr[u << 1].sum + tr[(u << 1) | 1].sum; }

void pushdown(int u) {
  auto &root = tr[u], &left = tr[u << 1], &right = tr[(u << 1) | 1];
  if (root.add) {
    left.add += root.add, left.sum += (LL)(left.r - left.l + 1) * root.add;
    right.add += root.add, right.sum += (LL)(right.r - right.l + 1) * root.add;
    root.add = 0;
  }
}

// 构建线段树：
// 操作中读取的所有端点，和端点隔开的所有开区间，设置为叶子节点。
void build(int u, int x, int y, int l, int r)
// x,y是arr的坐标, l,r是实际的数
// 当l == arr[x]时，左边为闭，否则为开
// 当r == arr[y]时，右边为闭，否则为开
{
  // 闭区间的递归出口
  if (l == r) {
    tr[u] = {l, r, 0, 0};
  }
  // 左开右闭区间的递归出口
  else if (l != arr[x] && x + 1 == y && l == r) {
    tr[u] = {l, r, 0, 0};
  } else if (l != arr[x] && x + 1 == y && l != r) {
    tr[u] = {l, r, 0, 0};
    tr[u << 1] = {l, r - 1, 0, 0};
    build((u << 1) | 1, y, y, r, r);
  }
  // 左开右闭区间
  else if (l != arr[x]) {
    tr[u] = {l, r, 0, 0};
    int mid = (x + y + 1) >> 1;  //上取整
    build(u << 1, x, mid, arr[x] + 1, arr[mid]);
    build((u << 1) | 1, mid, y, arr[mid] + 1, arr[y]);
    pushup(u);
  }
  // 闭区间
  else {
    tr[u] = {l, r, 0, 0};
    int mid = (x + y) >> 1;
    build(u << 1, x, mid, arr[x], arr[mid]);
    build((u << 1) | 1, mid, y, arr[mid] + 1, arr[y]);
    pushup(u);
  }
}

// 修改线段树
void modify(int u, int l, int r) {
  // 如果节点代表的区间在[l,r]内
  if (tr[u].l >= l && tr[u].r <= r) {
    tr[u].sum += (LL)(tr[u].r - tr[u].l + 1);
    tr[u].add += 1;
  } else {
    pushdown(u);
    int mid = tr[u << 1].r;              // mid = 6, l=4,r=4
    if (l <= mid) modify(u << 1, l, r);  //
    if (r > mid) modify((u << 1) | 1, l, r);
    pushup(u);
  }
}

LL query(int u, int l, int r) {
  if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;

  pushdown(u);
  // int mid = tr[u].l + tr[u].r >> 1;
  int mid = tr[u << 1].r;
  LL sum = 0;
  if (l <= mid) sum = query(u << 1, l, r);
  if (r > mid) sum += query((u << 1) | 1, l, r);
  return sum;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%s%d%d", op[i], &point[i << 1], &point[(i << 1) | 1]);
    arr[i << 1] = point[i << 1];
    arr[(i << 1) | 1] = point[(i << 1) | 1];
  }

  // 对所有的端点去重、排序
  quick_sort(arr, 0, 2 * m - 1);
  int i = 0, j = 0;
  while (i <= 2 * m - 1) {
    if (i == 0 || arr[i] != arr[i - 1]) {
      arr[j++] = arr[i];
    }
    i++;
  }

  // 用arr来build
  build(1, 0, j - 1, arr[0], arr[j - 1]);  // 闭区间

  // modify(1, 4, 4);
  // modify(1, 1, 10);
  // while(1);

  for (int i = 0; i < m; ++i) {
    int l = point[2 * i], r = point[2 * i + 1];
    if (*(op[i]) == 'H') {
      modify(1, l, r);
    } else {
      printf("%lld\n", query(1, l, r));
    }
  }

  return 0;
}
