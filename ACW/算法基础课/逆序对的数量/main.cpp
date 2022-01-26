#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int a[maxn], tmp[maxn];
typedef long long ll;

ll mergeCount(int q[], int l, int r) {
  if (l >= r) return 0;
  ll res = 0;
  int mid = l + r >> 1;
  res += mergeCount(q, l, mid) + mergeCount(q, mid + 1, r);

  int i = l, j = mid + 1, k = 0;
  while (i <= mid && j <= r) {
    if (q[i] <= q[j])
      tmp[k++] = q[i++];
    else {
      res += mid - i + 1;
      tmp[k++] = q[j++];
    }
  }
  while (i <= mid) {
    tmp[k++] = q[i++];
  }
  while (j <= r) {
    tmp[k++] = q[j++];
  }

  for (int i = 0, j = l; j <= r; ++i, ++j) q[j] = tmp[i];
  return res;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  cout << mergeCount(a, 0, n - 1) << endl;
}