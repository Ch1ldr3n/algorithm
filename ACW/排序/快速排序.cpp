#include <cstdio>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int q[N];

void quickSortJ(int q[], int l, int r) {
  //递归终止：1个元素无需排序
  if (l >= r) return;
  //分而治之
  // 1. 选择分界线x，将数组转化成小于等于x和大于等于x的两部分
  int x = q[l + r >> 1];
  // 2. 双指针扫描，并交换该交换的元素
  int i = l - 1, j = r + 1;  // i，j往外取一格，因为后面是do while
  while (i < j) {            // i超过j则扫描完毕
    do i++;
    while (q[i] < x);
    do j--;
    while (q[j] > x);
    // 此时，q[l,...,i-1] <= x, q[i] >= x, q[j+1,...,r] >= x, q[j] <= x
    if (i < j) swap(q[i], q[j]);
    // 此时, q[l, i] <= x, q[j, r] >= x
  }
  /*
      前面所有迭代（ij没相遇）都满足: q[l, i] <= x, q[j, r] >= x
      重点在最后一步, swap是一定不执行的。因此只能有 i >= j 且
      q[l,...,i-1] <= x, q[i] >= x, q[j+1,...,r] >= x, q[j] <= x
      q[l, ..., i-1, i, ...]
      q[..., j-1,j,j+1,...,r]
      => q[l,...,j] <= x, q[j+1,...,r] >= x 必然成立,
      => q[l,...,i-1] <= x, q[i,...,r] >= x 也必然成立.
  */
  //递归处理子问题
  quickSortJ(q, l, j), quickSortJ(q, j + 1, r);
  /*
      这里为什么用j分割，而不能用i分割呢？ 是为了对应上面x的选取方式。
      - 用j分割，则x不能取到q[r]，用i分割，则x不能取到q[l]。
      假设x取q[r]，q[l,...,r-1]<x. 则结束循环后i=r，j=r，
      [l,r] -> [l,r],[r+1,r]，造成无限递归
      - 如何形象理解记忆？
      j -> [l,j] -> j不能为r -> x不能取到q[r] -> x = q[l+r>>1]
  */
}

void quickSortI(int q[], int l, int r) {
  if (l >= r) return;
  int x = q[l + r + 1 >> 1], i = l - 1, j = r + 1;
  while (i < j) {
    do i++;
    while (q[i] < x);
    do j--;
    while (q[j] > x);
    if (i < j) swap(q[i], q[j]);
  }
  quickSortI(q, l, i - 1), quickSortI(q, i, r);
}

// 从大到小
void quickSortR(int q[], int l, int r) {
  if (l >= r) return;
  int x = q[l + r >> 1], i = l - 1, j = r + 1;
  while (i < j) {
    do i++;
    while (q[i] > x);  // 左半部分 >= x
    do j--;
    while (q[j] < x);  // 右半部分 <= x
    if (i < j) swap(q[i], q[j]);
  }
  quickSortR(q, l, j), quickSortR(q, j + 1, r);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &q[i]);
  quickSortJ(q, 0, n - 1);
  for (int i = 0; i < n; ++i) printf("%d ", q[i]);
  printf("\n");
}