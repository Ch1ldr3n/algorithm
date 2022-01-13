#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 85;
char s[maxn];

int main() {
  //   freopen("input.txt", "r", stdin);
  //   freopen("output.txt", "w", stdout);
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 1; i <= len; ++i) {
      int j;
      if (len % i == 0) {
        for (j = i; j < len; ++j) {
          if (s[j] != s[j % i]) break;
        }
        if (j == len) {
          printf("%d\n", i);
          break;
        }
      }
    }
    if (t) printf("\n");
  }
}