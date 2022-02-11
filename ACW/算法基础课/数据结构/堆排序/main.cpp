#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
如何手写一个堆
1. 插入一个数 heap[++sz]=x;up(sz);
2. 求集合中的最小值 heap[1]
3. 删除最小值 heap[1]=heap[sz];sz--;down(1);
4. 删除任意一个元素 heap[k]=heap[sz];sz--;down(k);up(k);
5. 修改任意一个元素 heap[k]=x;down(k);up(k);
堆是一颗完全二叉树（除了最后一层外上面所有节点都是满的，最后一层从左到右依次排布
小根堆为例，每个点都小于左右儿子，所以根节点是最小值
堆的存储用一维数组。从1开始。[1,2,3,...]
x的左儿子是2x，x的右儿子是2x+1
down(x) 往下调整
up(x)往上调整
*/

const int N = 100010;
int n, m;
int h[N], sz;

/*
     x
    / \
   2x 2x+1
*/
void down(int x) {
  int t = x;
  if (2 * x <= sz && h[t] > h[2 * x]) t = 2 * x;
  if (2 * x + 1 <= sz && h[t] > h[2 * x + 1]) t = 2 * x + 1;
  if (t != x) {
    swap(h[t], h[x]);
    down(t);
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> h[i];
  }
  for (int i = n / 2; i; i--) down(i);
  for (int i = 0; i < m; ++i) {
    cout << h[1] << " ";
    h[1] = h[sz--];
    down(1);
  }
  cout << endl;
}