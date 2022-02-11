#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int e[maxn], ne[maxn], head, idx;
// 每个下标对应一个结点。 head维护头结点的下标。

void init() { head = -1; }

// 在下标为k的结点右边插入新结点
void insert(int k, int x) {
  e[idx] = x;
  ne[idx] = ne[k];
  ne[k] = idx++;
}

// 删除下标为k的结点的右边那个结点
void remove(int k) { ne[k] = ne[ne[k]]; }

// 添加新结点为头结点
void newhead(int x) {
  e[idx] = x;
  ne[idx] = head;
  head = idx++;
}

int main() {
  int n;
  cin >> n;
  init();
  while (n--) {
    int k, x;
    char op[2];
    cin >> op;
    if (*op == 'H') {
      cin >> x;
      newhead(x);
    } else if (*op == 'D') {
      cin >> k;
      if (k)
        remove(k - 1);
      else
        head = ne[head];
    } else {
      cin >> k >> x;
      insert(k - 1, x);
    }
  }
  for (int i = head; i != -1; i = ne[i]) cout << e[i] << " ";
  cout << endl;
}