#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 3 4 2 7 5
//         i

/*
原理：对每个数，把它左边的所有数都存到栈中。但这个栈有一个可以利用的性质，就是可以缩减成一个单调增的栈。
为什么呢？因为如果左边的数比右边的数大，那么左边这个数就可以删除掉。
*/

const int maxn = 100010;
int stk[maxn], tt = -1;

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    // 根据当前的数处理栈中内容
    while (tt >= 0 && stk[tt] >= x) tt--;
    if (tt < 0)
      cout << -1 << " ";
    else
      cout << stk[tt] << " ";
    stk[++tt] = x;
  }
}