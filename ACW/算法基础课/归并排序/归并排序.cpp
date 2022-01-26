#include <cstdio>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int q[N];
int tmp[N];

void mergeSort(int q[], int l, int r) {
  // 递归终点
  if (l >= r) return;
  // 分而治之；与快排不同，归并排序先递归再处理，快排先处理再递归
  int mid = l + r >> 1;
  mergeSort(q, l, mid), mergeSort(q, mid + 1, r);
  // 此时得到排好序的两部分 [l, ..., mid] [mid+1, ..., r]
  int i = l, j = mid + 1, k = l;
  while (i <= mid && j <= r) {
    if (q[i] <= q[j])  // 比较两边最小值，谁更小谁入tmp
      tmp[k++] = q[i++];
    else
      tmp[k++] = q[j++];
  }
  // 最后左右总有一个先被扫描完，那么剩下的依次接在后面即可
  while (i <= mid) tmp[k++] = q[i++];
  while (j <= r) tmp[k++] = q[j++];
  for (int i = l; i <= r; ++i) q[i] = tmp[i];
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &q[i]);
  mergeSort(q, 0, n - 1);
  for (int i = 0; i < n; ++i) printf("%d ", q[i]);
  printf("\n");
}