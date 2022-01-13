/*给定N个整数，选择两个异或最大的结果*/

#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e5 + 10, M = 31 * N;

/*
    固定Ai，如何选出Aj使得Ai异或Aj最大

    Trie树
*/

int n;
int a[N];
int son[M][2], idx;

void insert(int x) {
  int p = 0;
  for (int i = 30; i >= 0; --i) {
    int u = (x >> i) & 1;
    if (!son[p][u]) son[p][u] = ++idx;
    p = son[p][u];
  }
}

int query(int x) {
  int ret = 0;
  int p = 0;
  for (int i = 30; i >= 0; --i) {
    int u = (x >> i) & 1;
    if (son[p][!u]) {
      ret += 1 << i;
      p = son[p][!u];
    } else
      p = son[p][u];
  }
  return ret;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    insert(a[i]);
  }
  int res = 0;
  for (int i = 0; i < n; ++i) {
    res = max(res, query(a[i]));
  }
  cout << res;
  return 0;
}