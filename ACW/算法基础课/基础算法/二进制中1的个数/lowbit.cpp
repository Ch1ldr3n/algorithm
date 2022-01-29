#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// n = 15 = [第3位]1  1  1  1[第0位]
// 第k位：(n >> k) & 1
// lowbit(x): 返回x二进制表示的最后一个1及其之后的所有数组成的二进制数
int lowbit(int x) { return x & (-x); }

int main() {
  int n;
  cin >> n;
  while (n--) {
    int x, s = 0;
    cin >> x;
    // for (int i = x; i; i -= lowbit(i)) s++;
    while (x) x -= lowbit(x) cout << s << " ";
  }
  cout << endl;
}