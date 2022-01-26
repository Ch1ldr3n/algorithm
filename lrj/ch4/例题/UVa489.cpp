/*
https://vjudge.net/problem/UVA-489
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 128;
char word[maxn], seq[maxn];
int win, lose;
int left, chance;

void guess(char ch) {
  int bad = 1;
  for (int i = 0, n = strlen(word); i < n; ++i) {
    if (word[i] == ch) {
      bad = 0;
      word[i] = ' ';
      left--;
    }
  }
  if (bad) chance--;
  if (!chance) lose = 1;
  if (!left) win = 1;
}

int main() {
  int rnd;
  while (scanf("%d%s%s", &rnd, word, seq) == 3 && rnd != -1) {
    printf("Round %d\n", rnd);
    win = lose = 0;
    left = strlen(word);
    chance = 7;
    for (int i = 0, n = strlen(seq); i < n; ++i) {
      guess(seq[i]);
      if (win || lose) break;
    }

    if (win)
      printf("You win.\n");
    else if (lose)
      printf("You lose.\n");
    else
      printf("You chickened out.\n");
  }
}