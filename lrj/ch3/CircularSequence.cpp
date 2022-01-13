#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 105;
char s[maxn];
int n;

inline bool lt(int p, int q) {
  for (int i = 0; i < n; ++i) {
    if (s[(p + i) % n] != s[(q + i) % n])
      return s[(p + i) % n] < s[(q + i) % n];
  }
  return false;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", s);
    int ans = 0;
    n = strlen(s);
    for (int i = 1; i < n; ++i) {
      if (lt(i, ans)) ans = i;
    }
    for (int i = 0; i < n; ++i) {
      putchar(s[(ans + i) % n]);
    }
    putchar('\n');
  }
  return 0;
}