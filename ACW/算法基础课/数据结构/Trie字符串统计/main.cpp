#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;
int son[maxn][26], cnt[maxn], idx;
char str[maxn];

void insert(char *str) {
  int p = 0;
  for (int i = 0; i < strlen(str); ++i) {
    int u = str[i] - 'a';
    if (!son[p][u]) son[p][u] = ++idx;
    p = son[p][u];
  }
  cnt[p]++;
}

int query(char *str) {
  int p = 0;
  for (int i = 0; i < strlen(str); ++i) {
    int u = str[i] - 'a';
    if (!son[p][u]) return 0;
    p = son[p][u];
  }
  return cnt[p];
}

int main() {
  int n;
  cin >> n;
  while (n--) {
    char op[2];
    cin >> op;
    cin >> str;
    if (*op == 'I')
      insert(str);
    else
      cout << query(str) << endl;
  }
}