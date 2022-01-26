#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int maxm = 64, maxn = 1024;
const char* DNA = "ACGT";
char seqs[maxm][maxn];
char IDX[256] = {0};

struct chcnt {
  char ch;
  int cnt;
};
bool operator<(const chcnt& a, const chcnt& b) {
  return a.cnt > b.cnt || a.cnt == b.cnt && a.ch < b.ch;
}

int main() {
  //   freopen("input.txt", "r", stdin);
  //   freopen("output.txt", "w", stdout);
  int T, m, n;
  scanf("%d", &T);
  for (int i = 0; i < 4; ++i) IDX[DNA[i]] = i;  // A->0, C->1, G->2, T->3
  chcnt css[4];
  while (T--) {
    scanf("%d%d\n", &m, &n);
    for (int i = 0; i < m; ++i) {
      scanf("%s", seqs[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 4; ++j) {
        css[j].ch = DNA[j];
        css[j].cnt = 0;
      }
      for (int j = 0; j < m; ++j) {
        css[IDX[seqs[j][i]]].cnt++;
      }
      sort(css, css + 4);
      printf("%c", css[0].ch);
      ans += m - css[0].cnt;
    }
    printf("\n%d\n", ans);
  }
  return 0;
}