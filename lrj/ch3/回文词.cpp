#include <cctype>
#include <cstdio>
#include <cstring>

const char* rev = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char* msg[] = {"not a palindrome", "a regular palindrome",
                     "a mirrored string", "a mirrored palindrome"};

char r(char ch) {  //将字符转换为镜像
  if (isalpha(ch)) return rev[ch - 'A'];
  return rev[ch - '0' + 25];
}

int main() {
  char s[30];  // 当前字符串
  while (scanf("%s", s) == 1) {
    int len = strlen(s);
    int p = 1, m = 1;
    for (int i = 0; i < (len + 1) / 2;
         ++i) {  // 01234 len=5  0123 len=4 (取字符串前一半的方法)
      if (s[i] != s[len - 1 - i]) p = 0;     //不是回文
      if (r(s[i]) != s[len - 1 - i]) m = 0;  //不是镜像
    }
    printf("%s -- is %s.\n\n", s, msg[m * 2 + p]);
  }
  return 0;
}