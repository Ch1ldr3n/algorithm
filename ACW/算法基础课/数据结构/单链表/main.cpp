#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int e[maxn], nxt[maxn], idx, head;
// init
head = -1;  // idx=0;

// head -> 0 -> 1 -> 2 -> 3 -> 4 -> -1[空集]

void insAsHead(int u) {
  e[idx] = u;
  ne[idx] = head;
  head = idx++;
}

void del(int k) { ne[k - 1] = ne[ne[k - 1]]; }

void ins(int u, int k) {
  e[idx] = u;
  ne[idx] = ne[k - 1];
  ne[k - 1] = idx++;
}

int main() {
  int n;
  cin >> n;
  while (n--) {
    char op[2];
    cin >> op;
    if (*op == 'H') {
      int x;
      cin >> x;
      insert(x);
    } else if (*op == 'D') {
      int k;
      cin >> k;
    }
  }
}
