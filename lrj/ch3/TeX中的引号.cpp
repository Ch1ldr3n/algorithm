#include <cstdio>
#include <cstring>
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int c; //这里是int，因为如果是char将无法和EOF区分（getchar返回int）
    int q = 1; // 1:左引号,0:右引号
    while ((c = getchar()) != EOF) {
        if (c == '"') {
            printf("%s", q ? "``" : "''");
            q = !q;
        } else {
            printf("%c", c);
        }
    }
    return 0;
}
