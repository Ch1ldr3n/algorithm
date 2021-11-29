#include <cstdio>
char s[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
int main()
{
    int c; //当前读入的字符
    while ((c = getchar()) != EOF) {
        int i;
        for (i = 0; s[i] && s[i] != c; i++)
            ; //找c在s中的索引。s[i]等价于s[i]!='\0'
        //至此，i要么出界，要么指向c
        if (s[i]) { //c在s中
            putchar(s[i - 1]);
        } else { //c不在s中
            putchar(c);
        }
    }
    return 0;
}