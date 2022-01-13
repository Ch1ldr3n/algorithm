#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1010;

int n, a[maxn], b[maxn], kase;
int ta[maxn], tb[maxn];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  while (scanf("%d", &n) == 1 && n) {
    printf("Game %d:\n", ++kase);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    while (1) {
      for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
      if (b[0] == 0) break;
      int c1 = 0, c2 = 0;
      for (int i = 0; i < n; ++i)
        if (a[i] == b[i]) c1++;
      memset(ta, 0, sizeof(ta));
      memset(tb, 0, sizeof(tb));
      for (int i = 0; i < n; ++i) {
        ta[a[i]]++;
        tb[b[i]]++;
      }
      for (int i = 1; i <= 9; ++i) c2 += (ta[i] < tb[i] ? ta[i] : tb[i]);
      c2 -= c1;
      printf("    (%d,%d)\n", c1, c2);
    }
  }
  return 0;
}