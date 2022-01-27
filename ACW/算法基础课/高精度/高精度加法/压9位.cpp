#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int base = 1e9, width = 9;

vector<int> add(vector<int> &a, vector<int> &b) {
  if (a.size() < b.size()) return add(b, a);
  vector<int> c;
  for (int i = 0, n = a.size(); i < n; ++i) {
    c.push_back(a[i]);
    if (i < b.size()) c[i] += b[i];
  }
  int t = 0;
  for (int i = 0, n = c.size(); i < n; ++i) {
    c[i] += t;
    t = c[i] / base;
    c[i] %= base;
  }
  if (t) c.push_back(t);
  return c;
}

int str2int(string str) {
  int res = 0;
  for (int i = 0, n = str.size(); i < n; ++i) {
    res = res * 10 + (str[i] - '0');
  }
  return res;
}

vector<int> str2vec(string str) {
  vector<int> res;
  int len = str.size();
  while (len >= width) {
    string tmp = str.substr(len - width, width);
    len -= width;
    res.push_back(str2int(tmp));
  }
  if (len) res.push_back(str2int(str.substr(0, len)));
  return res;
}

int main() {
  string sa, sb;
  cin >> sa >> sb;
  auto a = str2vec(sa);
  auto b = str2vec(sb);
  auto c = add(a, b);
  cout << c.back();
  for (int i = c.size() - 2; i >= 0; --i) {
    printf("%09d", c[i]);
  }
  puts("");
  return 0;
}
