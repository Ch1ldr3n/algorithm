#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 90;
char s[maxn];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", s);
    int last = 0;  // 此前连续O的个数
    int n = strlen(s);
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == 'O') {
        last++;
        res += last;
      } else {
        last = 0;
      }
    }
    printf("%d\n", res);
  }
}