#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  string sa;
  vector<int> a, c;
  int b;
  cin >> sa >> b;
  for (int i = sa.size() - 1; i >= 0; --i) a.push_back(sa[i] - '0');
  for (int i = 0; i < a.size(); ++i) {
    c.push_back(a[i] * b);
  }
  int t = 0;
  for (int i = 0; i < c.size(); ++i) {
    c[i] += t;
    t = c[i] / 10;
    c[i] %= 10;
  }
  while (t) {
    c.push_back(t % 10);
    t /= 10;
  }
  while (c.size() != 1 && c.back() == 0) c.pop_back();
  for (int i = c.size() - 1; i >= 0; i--) cout << c[i];
  cout << endl;
}