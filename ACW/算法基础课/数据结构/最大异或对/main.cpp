#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int son[31 * maxn][2], a[maxn], idx;

void insert(int num) {
  int p = 0;
  for (int i = 30; i >= 0; --i) {
    int u = (num >> i) & 1;
    if (!son[p][u]) son[p][u] = ++idx;
    p = son[p][u];
  }
}

int search(int num) {
  int p = 0, res = 0;
  for (int i = 30; i >= 0; --i) {
    int u = (num >> i) & 1;
    if (son[p][!u]) {
      res += 1 << i;
      p = son[p][!u];
    } else
      p = son[p][u];
  }
  return res;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i], insert(a[i]);
  int res = 0;
  for (int i = 0; i < n; ++i) res = max(res, search(a[i]));
  cout << res << endl;
}