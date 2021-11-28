#include <cstdio>
int main()
{
    int a, b, c, kase = 0;
    while (scanf("%d%d%d", &a, &b, &c) == 3 && (a || b || c)) {
        printf("Case %d: %.*f\n", ++kase, c, (a + 0.0) / b);
    }
}