#include <cstdio>
int main()
{
    int a, b, c, kase = 0;
    while (scanf("%d%d%d", &a, &b, &c) == 3) {
        kase++;
        bool answer = false;
        for (int i = 10; i <= 100; ++i) {
            if (i % 3 == a && i % 5 == b && i % 7 == c) {
                printf("Case %d: %d\n", kase, i);
                answer = true;
                break;
            }
        }
        if (!answer)
            printf("Case %d: No answer\n", kase);
    }
}