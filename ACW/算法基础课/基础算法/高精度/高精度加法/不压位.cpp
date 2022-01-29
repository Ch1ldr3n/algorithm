#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> a, b;

vector<int> add(vector<int>& a, vector<int>& b) {
  if (a.size() < b.size()) return add(b, a);
  vector<int> c;
  for (int i = 0, alen = a.size(); i < alen; ++i) {
    c.push_back(a[i]);
    if (i < b.size()) c[i] += b[i];
  }
  int t = 0;
  for (int i = 0, clen = c.size(); i < clen; ++i) {
    c[i] += t;
    t = c[i] / 10;
    c[i] = c[i] % 10;
  }
  if (t) c.push_back(t);
  return c;
}

int main() {
  string sa, sb;  // 123456, 789
  cin >> sa >> sb;
  int alen = sa.size(), blen = sb.size();
  for (int i = alen - 1; i >= 0; --i) a.push_back(sa[i] - '0');  // 6,5,4,3,2,1
  for (int i = blen - 1; i >= 0; --i) b.push_back(sb[i] - '0');  // 9,8,7
  auto c = add(a, b);
  for (int i = c.size() - 1; i >= 0; --i) cout << c[i];
  cout << endl;
}