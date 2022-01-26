#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int a[maxn];
int n, q;

int searchLeft(int u) {
  int l = 0, r = n - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (a[mid] >= u)
      r = mid;
    else
      l = mid + 1;
  }
  return l;
}

int searchRight(int u) {
  int l = 0, r = n - 1;
  while (l < r) {
    int mid = l + r + 1 >> 1;
    if (a[mid] <= u)
      l = mid;
    else
      r = mid - 1;
  }
  return l;
}

int main() {
  cin >> n >> q;
  for (int i = 0; i < n; ++i) cin >> a[i];
  while (q--) {
    int k;
    cin >> k;
    int l = searchLeft(k);
    if (a[l] != k) {
      cout << "-1 -1" << endl;
      continue;
    }
    int r = searchRight(k);
    cout << l << " " << r << endl;
  }
}