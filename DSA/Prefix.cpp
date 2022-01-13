#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 2e7 + 7;

int ne[N];  // next数组
int dp[N];  // next链的长度
char s[N];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  //构造next数组
  int i = 0;
  ne[0] = -1;
  int j = -1;
  while (i < n) {
    if (j == -1 || s[j] == s[i]) {
      i++;
      j++;
      ne[i] = j;
    } else
      j = ne[j];
  }
  //计算dp
  ll ans = 0;
  ne[0] = 0;
  for (int i = 1; i <= n; ++i) {
    dp[i] = dp[ne[i]] + 1;
  }
  for (int i = 1; i <= n; ++i) ans += (ll)dp[i];
  printf("%lld\n", ans);
  return 0;
}
