#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;

const char rev[] = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char *msg[] = {"is not a palindrome.", "is a regular palindrome.",
                     "is a mirrored string.", "is a mirrored palindrome."};

inline char r(char c) {
  if (isalpha(c)) return rev[c - 'A'];
  return rev[c - '0' + 25];
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  char s[30];
  while (scanf("%s", s) == 1) {
    int p = 1, m = 1;
    for (int i = 0, n = strlen(s); i < (n + 1) / 2; ++i) {
      if (s[i] != s[n - 1 - i]) p = 0;
      if (r(s[i]) != s[n - 1 - i]) m = 0;
    }
    int res = p + m * 2;
    printf("%s -- %s\n\n", s, msg[res]);
  }
  return 0;
}