#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#include "kth.h"

const int maxn = 5e5 + 10;
const int maxk = 2e6 + 10;
int X[maxn], Y[maxn], Z[maxn];  //分别对应原数组a，b，c的下标

//以三元组为元素建堆
struct Vec {
  int x, y, z;  // (x,y,z) -> (X[x],Y[y],Z[z])
  Vec(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
  Vec() : x(0), y(0), z(0) {}
  bool operator<(const Vec &w) {
    return compare(X[x], Y[y], Z[z], X[w.x], Y[w.y], Z[w.z]);
  }
};
// 小根堆
Vec h[maxk];
int size;

inline void up(int u) {
  // while 有父节点且u小于父节点
  while (u / 2 && h[u] < h[u / 2]) {
    auto tmp = h[u];
    h[u] = h[u / 2];
    h[u / 2] = tmp;
    u >>= 1;
  }
}
inline void down(int u) {
  int t = u;
  if ((u << 1) <= size && h[u << 1] < h[t]) t = u << 1;
  if ((u << 1 | 1) <= size && h[u << 1 | 1] < h[t]) t = u << 1 | 1;
  if (u != t) {
    // swap(h[u],h[t]);
    auto tmp = h[u];
    h[u] = h[t];
    h[t] = tmp;
    down(t);
  }
}

inline void swap(int &a, int &b) {
  int c = a;
  a = b;
  b = c;
}
inline bool lt(const int &x, const int &y, int flag) {
  if (flag == 1)                       // 比较a[x] < a[y] ?
    return compare(x, 1, 1, y, 1, 1);  // a[x]+b[1]+c[1]<a[y]+b[1]+c[1]
  else if (flag == 2)
    return compare(1, x, 1, 1, y, 1);
  else
    return compare(1, 1, x, 1, 1, y);
}

void quickSort(int q[], int l, int r, int flag) {
  if (l >= r) return;
  int i = l - 1, j = r + 1, x = q[l + r >> 1];
  while (i < j) {
    do i++;
    while (/*q[i] < x*/ lt(q[i], x, flag));
    do j--;
    while (/*q[j] > x*/ lt(x, q[j], flag));
    if (i < j) swap(q[i], q[j]);
  }
  quickSort(q, l, j, flag);
  quickSort(q, j + 1, r, flag);
}

void get_kth(int n, int k, int *x, int *y, int *z) {
  //预处理X，Y，Z。即将他们按照对应元素的大小排列
  // a[X[i]] < a[X[i+1]]
  for (int i = 1; i <= n; ++i) X[i] = Y[i] = Z[i] = i;
  quickSort(X, 1, n, 1);
  quickSort(Y, 1, n, 2);
  quickSort(Z, 1, n, 3);

  h[++size] = Vec(1, 1, 1);

  while (--k) {
    Vec v = h[1];
    //删除最小值
    h[1] = h[size];
    size--;
    down(1);
    if (v.z != n) {
      // insert (x,y,z+1)
      h[++size] = Vec(v.x, v.y, v.z + 1);
      up(size);
    }
    if (v.z == 1) {
      if (v.y == 1 && v.x != n) {
        // insert (x+1,y,z)
        h[++size] = Vec(v.x + 1, v.y, v.z);
        up(size);
      }
      if (v.y != n) {
        // insert (x,y+1,z)
        h[++size] = Vec(v.x, v.y + 1, v.z);
        up(size);
      }
    }
    *x = X[h[1].x], *y = Y[h[1].y], *z = Z[h[1].z];
  }
}