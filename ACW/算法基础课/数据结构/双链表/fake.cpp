#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int e[maxn], ne[maxn], pe[maxn], head, tail, idx;

void init() { head = tail = -1; }

void insAsHead(int x) {
  e[idx] = x;
  ne[idx] = head;
  pe[idx] = -1;
  pe[head] = idx;
  head = idx++;
}

void insAsTail(int x) {
  e[idx] = x;
  ne[idx] = -1;
  pe[idx] = tail;
  ne[tail] = idx;
  tail = idx++;
}

void del(int k) {
  ne[pe[k]] = ne[k];
  pe[ne[k]] = pe[k];
}

void insLeft(int k, int x) {
  e[idx] = x;
  ne[idx] = k;
  pe[idx] = pe[k];
  ne[pe[k]] = idx;
  pe[k] = idx++;
}

void insRight(int k, int x) {
  e[idx] = x;
  ne[idx] = ne[k];
  pe[idx] = k;
  pe[ne[k]] = idx;
  ne[k] = idx++;
}

int main() {
  int n;
  cin >> n;
  while (n--) {
    char op[2];
    cin >> op;
    if (*op == 'L') {
      int x;
      cin >> x;
      insAsHead(x);
    } else if (*op == 'R') {
      int x;
      cin >> x;
      insAsTail(x);
    } else if (*op == 'D') {
      int k;
      cin >> k;
      del(k - 1);
    } else if (*op == 'I') {
      int k, x;
      cin >> k >> x;
      if (op[1] == 'L')
        insLeft(k - 1, x);
      else
        insRight(k - 1, x);
    }
  }
  for (int i = head; i != -1; i = ne[i]) cout << e[i] << " ";
  cout << endl;
}