#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> mul(vector<int> &a, int b) {
  vector<int> c;
  int t = 0;
  for (int i = 0; i < a.size() || t; ++i) {
    if (i < a.size()) t += a[i] * b;
    c.push_back(t % 10);
    t /= 10;
  }
  while (c.size() != 1 && c.back() == 0) c.pop_back();
  return c;
}

int main() {
  string sa;
  int b;
  vector<int> a;
  cin >> sa >> b;
  for (int i = sa.size() - 1; i >= 0; i--) a.push_back(sa[i] - '0');
  auto c = mul(a, b);
  for (int i = c.size() - 1; i >= 0; --i) cout << c[i];
  cout << endl;
  return 0;
}