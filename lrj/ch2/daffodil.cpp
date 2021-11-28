#include <cstdio>
int main()
{
    for (int n = 100; n < 1000; ++n) {
        int a = n / 100, b = (n / 10) % 10, c = n % 10;
        if (n == a * a * a + b * b * b + c * c * c)
            printf("%d\n" n);
    }
}