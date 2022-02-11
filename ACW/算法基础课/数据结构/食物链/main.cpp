#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int N = 50010;
int p[N];  //记录第i个点的父节点
int d[N];  //记录第i个点到父节点的距离

//寻找第i个点的根节点，路径压缩
int find(int x) {
  if (p[x] != x) {
    int u = find(p[x]);
    d[x] += d[p[x]];
    p[x] = u;
  }
  return p[x];
}

int main() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) p[i] = i;
  int res = 0;
  while (k--) {
    int t, x, y;
    cin >> t >> x >> y;
    if (x > n || y > n) {
      res++;
      continue;
    }
    int px = find(x), py = find(y);
    if (t == 1) {
      if (px == py && (d[x] - d[y]) % 3)
        res++;
      else if (px != py) {
        p[px] = py;
        d[px] = d[y] - d[x];
      }
    } else {
      if (px == py && (d[x] - d[y] - 1) % 3)
        res++;
      else if (px != py) {
        p[px] = py;
        d[px] = d[y] + 1 - d[x];
      }
    }
  }
  cout << res << endl;
}