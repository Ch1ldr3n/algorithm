#include <cstdio>
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int t = (n - i) * 2 - 1;
        for (int j = 0; j < i; ++j)
            printf(" ");
        for (int j = 0; j < t; ++j)
            printf("#");
        for (int j = 0; j < i; ++j)
            printf(" ");
        printf("\n");
    }
    return 0;
}