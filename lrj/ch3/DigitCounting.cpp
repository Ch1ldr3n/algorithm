#include <cstdio>
using namespace std;

const int maxn = 10010;

int a[maxn][10];
// 对任一个数num，a[num][i]存储1～num出现的所有i，i=0,1,...,9

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  a[1][1] = 1;
  for (int i = 2; i < maxn; ++i) {
    for (int j = 0; j < 10; ++j) a[i][j] = a[i - 1][j];
    int k = i;
    while (k > 0) {
      a[i][k % 10]++;
      k /= 10;
    }
  }
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 10; ++i) {
      if (i == 0)
        printf("%d", a[n][0]);
      else
        printf(" %d", a[n][i]);
    }
    printf("\n");
  }
}