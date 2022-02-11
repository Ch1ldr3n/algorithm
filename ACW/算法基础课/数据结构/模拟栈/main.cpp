#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int st[maxn], tt;

void init() { tt = -1; }
void push(int x) { st[++tt] = x; }
void pop() { tt--; }
bool empty() { return tt < 0; }
int query() { return st[tt]; }

int main() {
  init();
  int n;
  cin >> n;
  while (n--) {
    string op;
    cin >> op;
    if (op == "push") {
      int x;
      cin >> x;
      push(x);
    } else if (op == "pop")
      pop();
    else if (op == "empty") {
      if (empty())
        puts("YES");
      else
        puts("NO");
    } else {
      cout << query() << endl;
    }
  }
}