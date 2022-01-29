#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int a[maxn], n, s[maxn];

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) {
    int u = a[i];
    while (u) {
      s[i] += u & 1;
      u >>= 1;
    }
  }
  for (int i = 0; i < n; ++i) cout << s[i] << " ";
  cout << endl;
}