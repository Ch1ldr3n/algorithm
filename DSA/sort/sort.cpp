#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#include "sort.h"

inline bool lt(int a, int b) {
  int min, max;
  compare(a, a, b, &max, &min);
  return a == min;
}

void merge2(int q[], int a[], int l1, int b[], int l2) {
  int p1, p2, idx;
  p1 = p2 = idx = 0;
  while (p1 < l1 && p2 < l2) {
    if (lt(a[p1], b[p2]))
      q[idx++] = a[p1++];
    else
      q[idx++] = b[p2++];
  }
  while (p1 < l1) q[idx++] = a[p1++];
  while (p2 < l2) q[idx++] = b[p2++];
}

void merge3(int q[], int a[], int l1, int b[], int l2, int c[], int l3) {
  int p1, p2, p3, idx, min, max;
  p1 = p2 = p3 = idx = 0;
  if (l1 && l2 && l3) {
    while (p1 < l1 && p2 < l2 && p3 < l3) {
      compare(a[p1], b[p2], c[p3], &max, &min);
      q[idx++] = min;
      if (a[p1] == min) p1++;
      if (b[p2] == min) p2++;
      if (c[p3] == min) p3++;
    }
  }
  if (p1 == l1) {
    merge2(q + idx, b + p2, l2 - p2, c + p3, l3 - p3);
  } else if (p2 == l2) {
    merge2(q + idx, a + p1, l1 - p1, c + p3, l3 - p3);
  } else
    merge2(q + idx, a + p1, l1 - p1, b + p2, l2 - p2);
}

void merge4(int q[], int a[], int l1, int b[], int l2, int c[], int l3, int d[],
            int l4) {
  int p1, p2, p3, p4;
  p1 = p2 = p3 = p4 = 0;
  int idx = 0;
  int min, max;
  char flag;
  // 确保4个数组均不为空，否则退化为三路归并
  if (l1 && l2 && l3 && l4) {
    //前三列比较，取最大者
    int tmax, tmin;
    compare(a[0], b[0], c[0], &tmax, &tmin);
    if (tmax == a[0])
      flag = 'a';
    else if (tmax == b[0])
      flag = 'b';
    else
      flag = 'c';
    while (p1 < l1 && p2 < l2 && p3 < l3 && p4 < l4) {
      if (flag == 'a') {
        compare(b[p2], c[p3], d[p4], &max, &min);
      } else if (flag == 'b') {
        compare(a[p1], c[p3], d[p4], &max, &min);
      } else if (flag == 'c') {
        compare(a[p1], b[p2], d[p4], &max, &min);
      } else
        compare(a[p1], b[p2], c[p3], &max, &min);
      q[idx++] = min;
      if (a[p1] == max) flag = 'a';
      if (b[p2] == max) flag = 'b';
      if (c[p3] == max) flag = 'c';
      if (d[p4] == max) flag = 'd';
      if (a[p1] == min) p1++;
      if (b[p2] == min) p2++;
      if (c[p3] == min) p3++;
      if (d[p4] == min) p4++;
    }
  }
  //此时只剩下三路
  if (p1 == l1) {
    merge3(q + idx, b + p2, l2 - p2, c + p3, l3 - p3, d + p4, l4 - p4);
  } else if (p2 == l2) {
    merge3(q + idx, a + p1, l1 - p1, c + p3, l3 - p3, d + p4, l4 - p4);
  } else if (p3 == l3) {
    merge3(q + idx, a + p1, l1 - p1, b + p2, l2 - p2, d + p4, l4 - p4);
  } else if (p4 == l4) {
    merge3(q + idx, a + p1, l1 - p1, b + p2, l2 - p2, c + p3, l3 - p3);
  }
}

void mergeSort(int q[], int l, int r) {
  if (l >= r) return;
  // 均分成4个数组a,b,c,d
  int s1 = (r - l) / 4;
  int s2 = (r - l) * 2 / 4;
  int s3 = (r - l) * 3 / 4;
  // [l, l+s1] [l+s1+1, l+s2] [l+s2+1,l+s3] [l+s3+1,r]
  int l1 = s1 + 1;
  int l2 = s2 - s1;
  int l3 = s3 - s2;
  int l4 = r - l - s3;
  int *a = new int[l1 + 1];
  int *b = new int[l2 + 1];
  int *c = new int[l3 + 1];
  int *d = new int[l4 + 1];
  memcpy(a, q + l, sizeof(int) * l1);
  memcpy(b, q + l + s1 + 1, sizeof(int) * l2);
  memcpy(c, q + l + s2 + 1, sizeof(int) * l3);
  memcpy(d, q + l + s3 + 1, sizeof(int) * l4);
  mergeSort(a, 0, l1 - 1);
  mergeSort(b, 0, l2 - 1);
  mergeSort(c, 0, l3 - 1);
  mergeSort(d, 0, l4 - 1);
  merge4(q, a, l1, b, l2, c, l3, d, l4);
  delete[] a;
  delete[] b;
  delete[] c;
  delete[] d;
}

void sort(int n, int limit, int *a) { mergeSort(a, 0, n - 1); }