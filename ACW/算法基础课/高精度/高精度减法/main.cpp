#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool lt(string &a, string &b) {
  if (a.size() != b.size()) return a.size() < b.size();
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) return a[i] < b[i];
  }
  return false;
}

vector<int> sub(vector<int> &a, vector<int> &b) {
  vector<int> c;  // a: 3,2,8  b: 5,4,6
  int t = 0;      // a: 123 b: 45  8,7,1
  // t = 1表示借位了， t = 0表示没有借位。
  /*
  while (a.size() > b.size()) b.push_back(0);
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] - t >= b[i]) {
      c.push_back(a[i] - t - b[i]);
      t = 0;
    } else {
      c.push_back(a[i] - t + 10 - b[i]);
      t = 1;
    }
  }
  */
  for (int i = 0; i < a.size(); ++i) {
    t = a[i] - t;
    if (i < b.size()) t -= b[i];
    c.push_back((t + 10) % 10);
    // t必是个位数。如果t为正，则不变；t为负则加10。
    if (t < 0)
      t = 1;
    else
      t = 0;
  }
  while (c.back() == 0 && c.size() != 1) c.pop_back();
  return c;
}

int main() {
  string sa, sb;
  cin >> sa >> sb;
  vector<int> a, b;
  for (int i = sa.size() - 1; i >= 0; i--) a.push_back(sa[i] - '0');
  for (int i = sb.size() - 1; i >= 0; i--) b.push_back(sb[i] - '0');
  vector<int> c;
  if (lt(sa, sb)) {
    cout << "-";
    c = sub(b, a);
  } else
    c = sub(a, b);

  for (int i = c.size() - 1; i >= 0; --i) cout << c[i];
  cout << endl;
}