#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> div(vector<int> &a, int b, int &r) {
  r = 0;
  vector<int> c;
  for (int i = a.size() - 1; i >= 0; --i) {
    r = r * 10 + a[i];
    c.push_back(r / b);
    r %= b;
  }
  reverse(c.begin(), c.end());
  while (c.size() != 1 && c.back() == 0) c.pop_back();
  return c;
}

int main() {
  string sa;
  vector<int> a;
  int b;
  cin >> sa >> b;
  for (int i = sa.size() - 1; i >= 0; --i) a.push_back(sa[i] - '0');
  int r;
  auto c = div(a, b, r);
  for (int i = c.size() - 1; i >= 0; --i) cout << c[i];
  cout << endl;
  cout << r << endl;
}