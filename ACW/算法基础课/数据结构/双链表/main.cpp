#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;

int e[maxn], l[maxn], r[maxn], idx;
// 我们把0号结点作为头哨兵，1号结点作为尾哨兵，哨兵不存储有用的数据。

void init() {
  r[0] = 1;
  l[1] = 0;
  idx = 2;  //前两个序号都被占用了，所以从2开始存储数据
}  // [0] <-> [1]

// 在序号为k的结点右边插入x
void insert(int k, int x) {
  e[idx] = x;
  l[idx] = k;
  r[idx] = r[k];
  l[r[k]] = idx;
  r[k] = idx++;
}

// 删除序号为k的结点
void remove(int k) {
  r[l[k]] = r[k];
  l[r[k]] = l[k];
}

int main() {
  int n;
  cin >> n;
  init();
  while (n--) {
    string op;
    cin >> op;
    if (op == "L") {
      int x;
      cin >> x;
      insert(0, x);
    } else if (op == "R") {
      int x;
      cin >> x;
      insert(l[1], x);
    } else if (op == "D") {
      int k;
      cin >> k;
      remove(k + 1);
    } else if (op == "IL") {
      int k, x;
      cin >> k >> x;
      insert(l[k + 1], x);
    } else {
      int k, x;
      cin >> k >> x;
      insert(k + 1, x);
    }
  }
  for (int i = r[0]; i != 1; i = r[i]) cout << e[i] << " ";
  cout << endl;
}
