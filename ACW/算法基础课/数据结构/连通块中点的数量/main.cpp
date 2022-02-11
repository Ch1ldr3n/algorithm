#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int N = 100010;
int p[N], cnt[N];

int find(int x) {
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) p[i] = i, cnt[i] = 1;
  int m;
  cin >> m;
  while (m--) {
    char op[3];
    int a, b;
    cin >> op >> a;
    if (*op == 'C') {
      cin >> b;
      if (find(a) != find(b))
        cnt[find(b)] += cnt[find(a)], p[find(a)] = find(b);
      //这里不能先改变p，因为这会改变find的结果。最好先把findab存下来。
    } else if (op[1] == '1') {
      cin >> b;
      find(a) == find(b) ? puts("Yes") : puts("No");
    } else
      cout << cnt[find(a)] << endl;
  }
}