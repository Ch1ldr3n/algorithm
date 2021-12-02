#include <cstdio>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int q[N];

// 求q[l,...,r]里第k大的数, k >= 1 且 k <= r-l+1
int quickSelect(int q[], int l, int r, int k) {
  // 递归终点：l == r， (隐含k == 1)
  if (l >= r) return q[l];
  int x = q[l + r >> 1], i = l - 1, j = r + 1;
  while (i < j) {
    do i++;
    while (q[i] < x);
    do j--;
    while (q[j] > x);
    if (i < j) swap(q[i], q[j]);
  }
  // q[l,...,j], q[j+1,...,r]
  if (k > j - l + 1)
    return quickSelect(q, j + 1, r, k - j + l - 1);
  else
    return quickSelect(q, l, j, k);
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) scanf("%d", &q[i]);
  // q[1, ..., n]

  printf("%d\n", quickSelect(q, 1, n, k));
  return 0;
}