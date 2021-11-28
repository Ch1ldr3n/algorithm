#include <cstdio>

int main()
{
    int n, m, kase = 0;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        double s = 0;
        for (long long i = n; i <= m; ++i) {
            double fre = (double)(i * i);
            s += 1.0 / fre;
        }
        printf("Case %d: %.5f\n", ++kase, s);
    }
}