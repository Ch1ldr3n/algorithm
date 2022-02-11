#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int q[maxn], hh, tt = -1;

int main() {
  int n;
  cin >> n;
  while (n--) {
    string op;
    cin >> op;
    if (op == "push") {
      int x;
      cin >> x;
      q[++tt] = x;
    } else if (op == "pop") {
      ++hh;
    } else if (op == "empty") {
      if (hh <= tt)
        puts("NO");
      else
        puts("YES");
    } else {
      cout << q[hh] << endl;
    }
  }
}