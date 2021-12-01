#include <cstdio>
#include <cstring>
using namespace std;

int n;                   // 序列总长度。本题其实是幌子。
int m;                   // 操作数。对应m个区间，2m个端点
const int M = 2e5 + 10;  // m的最大值， 离散化总点数最大为2M
struct Util {
  char op;
  int l, r;
} qh[M];  // 存储操作序列，以便最后统一执行

struct Node {
  int l, r;
  int add;  // 懒标记
  int sum;  // 区间和
} tr[M << 3];

int alls[2 * M], idx;  //存储所有待离散化的值

inline void swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

// 离散化前->离散化后
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

void show_1() {
  for (int i = 1; i <= idx; ++i) printf("%d ", alls[i]);
  printf("\n");
}

int main() {
  scanf("%d%d", &n, &m);

  // m次操作，一共涉及到2m个点。对这些点做离散化处理
  char op[2];
  int l, r;
  for (int i = 0; i < m; ++i) {
    scanf("%s%d%d", op, &l, &r);
    qh[i] = {op[0], l, r};
    alls[++idx] = l;
    alls[++idx] = r;
  }

  //离散化
  // 排序
  quickSort(alls, 1, idx);
  // 去重
  uniquify(alls, 1, idx);
  // alls[1, idx]
  //   show_1();
  // 建树
}
