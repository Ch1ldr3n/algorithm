#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int n, m, x;
int a[maxn], b[maxn];

int main() {
  cin >> n >> m >> x;
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < m; ++i) cin >> b[i];
  for (int i = 0, j = m - 1; i < n; ++i) {
    while (0 < j && a[i] + b[j - 1] >= x) j--;
    if (a[i] + b[j] == x) {
      cout << i << " " << j << endl;
      break;
    }
  }
}