#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100005;

int ans[maxn];

int main() {
  freopen("input.txt", "r", stdin);
  for (int i = 1; i <= 100000; ++i) {
    int sum = i;
    int x = i;
    while (x > 0) {  // 1234
      sum += x % 10;
      x /= 10;
    }
    if (ans[sum] == 0 || i < ans[sum]) ans[sum] = i;
  }
  int m;
  scanf("%d", &m);
  while (m--) {
    int n;
    scanf("%d", &n);
    printf("%d\n", ans[n]);
  }
  return 0;
}