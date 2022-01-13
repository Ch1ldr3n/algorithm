// 1 2 3 4 5 6 7 8 9 10
// o n n o n n n n o n

#include <cstdio>
#include <cstring>
#define maxn 1010
int a[maxn];  // 模拟所有灯灯情况
int main() {
  int n;  // 灯的总数
  int k;  // 人的总数
  scanf("%d%d", &n, &k);
  memset(a, 0, sizeof(a));          // 初始化灯为全灭
  for (int i = 1; i <= k; ++i) {    //遍历所有人
    for (int j = 1; j <= n; ++j) {  //遍历所有灯
      if (j % i == 0) {             //若灯编号是人编号的倍数
        a[j] = !a[j];               //则操作一次灯
      }
    }
  }
  // 输出
  bool first = true;  //将第一个和后面的数据区分开，因为格式不同。
  for (int i = 1; i <= n; ++i) {
    if (a[i]) {
      if (first)
        first = 0;
      else
        printf(" ");
      printf("%d", i);
    }
  }
  printf("\n");
  return 0;
}
