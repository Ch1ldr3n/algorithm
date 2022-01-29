#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int n, m;
int a[maxn], b[maxn];

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < m; ++i) cin >> b[i];
  int j = 0;
  for (int i = 0; i < n; ++i, ++j) {
    while (j < m && b[j] != a[i]) j++;
  }
  if (j <= m)
    puts("Yes");
  else
    puts("No");
}