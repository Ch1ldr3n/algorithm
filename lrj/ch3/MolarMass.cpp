#include <cctype>
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
    double ans = 0;
    scanf("%s", s);
    int n = strlen(s);
    for (int i = 0; i < n; ++i) {
      int j = i;
      int num = 1;
      if (j + 1 < n && isdigit(s[j + 1])) {
        num = s[i + 1] - '0';
        i++;
        if (j + 2 < n && isdigit(s[j + 2])) {
          num = num * 10 + s[j + 2] - '0';
          i++;
        }
      }

      if (s[j] == 'C')
        ans += 12.01 * num;
      else if (s[j] == 'H')
        ans += 1.008 * num;
      else if (s[j] == 'O')
        ans += 16.00 * num;
      else
        ans += 14.01 * num;
    }
    printf("%.3lf\n", ans);
  }
}