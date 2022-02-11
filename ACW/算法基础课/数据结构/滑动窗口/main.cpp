#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 1000010;
int a[maxn], q[maxn], hh, tt = -1;
// 1 3 -1 -3 5 3 6 7
// ------
int main() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) {
    // 起始位置i-k+1, 结束位置i
    if (hh <= tt && q[hh] < i - k + 1) hh++;
    while (hh <= tt && a[q[tt]] >= a[i]) tt--;
    q[++tt] = i;
    if (i >= k - 1) cout << a[q[hh]] << " ";
  }
  cout << endl;
  hh = 0, tt = -1;
  for (int i = 0; i < n; ++i) {
    if (hh <= tt && q[hh] < i - k + 1) hh++;
    while (hh <= tt && a[q[tt]] <= a[i]) tt--;
    q[++tt] = i;
    if (i >= k - 1) cout << a[q[hh]] << " ";
  }
  cout << endl;
}