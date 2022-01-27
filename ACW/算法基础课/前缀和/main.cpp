#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 1e5 + 10;
int a[maxn], s[maxn];
int n, m;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
  while (m--) {
    int l, r;
    cin >> l >> r;
    cout << s[r] - s[l - 1] << endl;
  }
}