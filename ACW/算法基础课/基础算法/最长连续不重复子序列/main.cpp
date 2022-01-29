#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int a[maxn];
int n;
int vis[maxn];

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  int res = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    vis[a[i]]++;
    while (j <= i && vis[a[i]] > 1) vis[a[j++]]--;
    res = max(res, i - j + 1);
  }

  cout << res << endl;
}