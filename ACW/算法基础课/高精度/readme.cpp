#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> add(vector<int> &a, vector<int> &b) {
  if (a.size() < b.size()) return add(b, a);
  vector<int> c;
  int t = 0;
  for (int i = 0; i < a.size(); ++i) {
    t += a[i];
    if (i < b.size()) t += b[i];
    c.push_back(t % 10);
    t /= 10;
  }
  if (t) c.push_back(t);
  return c;
}

// a >= b
vector<int> sub(vector<int> &a, vector<int> &b) {
  vector<int> c;
  int t = 0;
  for (int i = 0; i < a.size(); ++i) {
    t = a[i] - t;
    if (i < b.size()) t -= b[i];
    c.push_back((t + 10) % 10);
    if (t < 0)
      t = 1;
    else
      t = 0;
  }
  while (c.size() != 1 && c.back() == 0) c.pop_back();
  return c;
}

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

vector<int> div(vector<int> &a, int b, int &r) {
  vector<int> c;
  r = 0;
  // 这里和其他三个不一样，要从高位到低位
  for (int i = a.size() - 1; i >= 0; --i) {
    r = r * 10 + a[i];
    c.push_back(r / b);
    r %= b;
  }
  reverse(c.begin(), c.end());
  while (c.size() != 1 && c.back() == 0) c.pop_back();
  return c;
}