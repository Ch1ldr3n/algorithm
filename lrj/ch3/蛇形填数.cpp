/*
  10 11 12 1
  9  16 13 2
  8  15 14 3
  7  6  5  4
*/
#include <cstdio>
#include <cstring>
#define maxn 20
int a[maxn][maxn];

int main()
{
    int n; //矩阵大小
    int x, y; // 当前坐标
    int tot = 0; //当前待填的数
    scanf("%d", &n);
    memset(a, 0, sizeof(a)); //初始化为0，方便判断这个格子有没有走过
    tot = a[x = 0][y = n - 1] = 1; //填上第一个数
    //每当进入这个循环，处于这样的状态：tot已填完，准备填tot+1；
    while (tot < n * n) { //为何不是<=，因为下文填的是++tot
        //容易缺少条件的后半句。
        while (x < n - 1 && !a[x + 1][y]) { //预判是否越界
            a[++x][y] = ++tot;
        }
        while (y > 0 && !a[x][y - 1]) {
            a[x][--y] = ++tot;
        }
        while (x > 0 && !a[x - 1][y]) {
            a[--x][y] = ++tot;
        }
        while (y < n - 1 && !a[x][y + 1]) {
            a[x][++y] = ++tot;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%3d", a[i][j]); //每个整数占3位，不够的用空格补
        }
        printf("\n");
    }
    return 0;
}
