/*
2357
<1>
  775
X  33
-----
 2325
2325 
-----
25575

The number of solutions = 1
*/

#include <cstdio>
#include <cstring>
char s[12], buff[99];
int main()
{
    scanf("%s", s);
    int kase = 0;
    for (int abc = 111; abc < 1000; ++abc) {
        for (int de = 11; de < 100; ++de) {
            //判断abc*de是否合法
            int x = abc * (de % 10);
            int y = abc * (de / 10);
            int z = abc * de;
            sprintf(buff, "%d%d%d%d%d", abc, de, x, y, z); //输出到字符数组
            bool ok = true;
            for (int i = 0, n = strlen(buff); i < n; ++i) {
                if (strchr(s, buff[i]) == NULL)
                    ok = false;
            }
            if (ok) {
                printf("<%d>\n", ++kase);
                //打印对应的竖式
                printf("%5d\nX%4d\n-----\n%5d\n%4d \n-----\n%5d\n\n", abc, de, x, y, z);
            }
        }
    }
    printf("The number of solutions = %d\n", kase);
    return 0;
}