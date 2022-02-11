#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
并查集：将两个集合合并，询问两个元素是否在一个集合当中。
基本原理
每个集合用一棵树来表示。树根的编号就是整个集合的编号。每个节点存储它的父节点。p[x]表示x的父节点。
问题1:如何判断树根：if(p[x]==x)
问题2: 如何求x的集合编号：while(p[x]!=x) x=p[x]
问题3:如何合并两个集合，p[x]=y
第2步复杂度还是有点高，优化：
找根节点时，将路径上的所有点都直接指向根节点
加完这个优化之后基本可以按成O(1)的复杂度了
这个叫路径压缩
还有一个按秩合并
*/
const int N = 100010;
int p[N];

//返回x的根节点编号 + 路径压缩
int find(int x) {
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) p[i] = i;
  while (m--) {
    char op[2];
    int a, b;
    cin >> op >> a >> b;
    if (*op == 'M')
      p[find(a)] = find(b);
    else
      find(a) == find(b) ? puts("Yes") : puts("No");
  }
}