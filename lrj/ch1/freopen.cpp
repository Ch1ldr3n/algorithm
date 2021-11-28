#include <cstdio>
#define INF 2e9
int main()
{
#ifdef DEBUG
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    int x, n = 0, min = INF, max = -INF, s = 0; //当前值，总数，最小值，最大值，总和
    while (scanf("%d", &x) == 1) {
        s += x;
        if (x < min)
            min = x;
        if (x > max)
            max = x;
        n++;
    }
    printf("%d %d %.3f\n", min, max, (double)s / n);
    return 0;
}