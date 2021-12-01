// https://www.acwing.com/problem/content/804/
// 离散化 模板题
/*
假定有一个无限长的数轴，数轴上每个坐标上的数都是 0。
现在，我们首先进行 n 次操作，每次操作将某一位置 x 上的数加 c。
接下来，进行 m 次询问，每个询问包含两个整数 l 和 r，你需要求出在区间
[l,r]之间的所有数的和。
*/

#include <cstdio>

inline void swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

int n, m;                //点数，区间数
const int N = 1e5 + 10;  // n和m的最大值
// 所以涉及到的数轴上的点总共是n+2m <= 3*N

int alls[3 * N], idx;  //存储所有待离散化的点, [1, idx]
struct Add {
  int x, c;
} add[N];  //存储n个x,c
struct Range {
  int l, r;
} query[N];  //存储m个区间
int a[N], s[N];

int find(int x) {
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

void quickSort(int q[], int l, int r) {
  if (l >= r) return;
  int x = q[l + r >> 1], i = l - 1, j = r + 1;
  while (i < j) {
    do i++;
    while (q[i] < x);
    do j--;
    while (q[j] > x);
    if (i < j) swap(q[i], q[j]);
  }
  quickSort(q, l, j), quickSort(q, j + 1, r);
}

void uniquify(int q[], int l, int &r) {
  int i = 0, j = 0;
  while (++j <= r) {
    if (q[j] != q[i]) q[++i] = q[j];
  }
  r = i;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    int x, c;
    scanf("%d%d", &x, &c);
    add[i] = {x, c};
    alls[++idx] = x;
  }
  for (int i = 0; i < m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    query[i] = {l, r};
    alls[++idx] = l;
    alls[++idx] = r;
  }

  // 离散化
  // 排序
  quickSort(alls, 1, idx);
  // 去重
  uniquify(alls, 1, idx);
  // alls[1, idx]

  //处理插入
  for (int i = 0; i < n; ++i) {
    a[find(add[i].x)] += add[i].c;
  }

  //预处理前缀和
  for (int i = 1; i <= idx; ++i) {
    s[i] = s[i - 1] + a[i];
  }

  //处理查询
  for (int i = 0; i < m; ++i) {
    int l = find(query[i].l), r = find(query[i].r);
    printf("%d\n", s[r] - s[l - 1]);
  }
  return 0;
}
