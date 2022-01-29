#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int a[maxn], s[maxn];
int n, m;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> s[i];
  for (int i = 1; i <= n; ++i) a[i] = s[i] - s[i - 1];
  while (m--) {
    int l, r, c;
    cin >> l >> r >> c;
    a[l] += c;
    a[r + 1] -= c;
  }
  for (int i = 1; i <= n; ++i) {
    s[i] = s[i - 1] + a[i];
    cout << s[i] << " ";
  }
  cout << endl;
}