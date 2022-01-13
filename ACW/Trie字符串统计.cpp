/*
    Trie树：用于快速插入和查询字符串
*/

#include <iostream>
using namespace std;

const int N = 1e5 + 10;       // 字符串最大长度
int son[N][26], cnt[N], idx;  // cnt大小如何确定？ 字符串总长度

int insert(char str[]) {
  int p = 0;
  for (int i = 0; str[i]; ++i) {
    int u = str[i] - 'a';
    if (!son[p][u]) son[p][u] = ++idx;
    p = son[p][u];
  }
  cnt[p]++;
}

int query(char str[]) {
  int p = 0;
  for (int i = 0; str[i]; ++i) {
    int u = str[i] - 'a';
    if (!son[p][u]) return 0;
    p = son[p][u];
  }
  return cnt[p];
}

int main() {
  int n;
  cin >> n;
  char op[2], str[N];
  while (n--) {
    scanf("%s%s", op, str);
    if (*op == 'I')
      insert(str);
    else
      cout << query(str) << endl;
  }
  return 0;
}
