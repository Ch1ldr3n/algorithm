#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 100010;

struct Range {
  int l, r;
  bool operator<(const Range& w) { return l < w.l; }
} r[maxn];

vector<pair<int, int>> res;

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> r[i].l >> r[i].r;
  sort(r, r + n);
  int st = r[0].l, ed = r[0].r;
  for (int i = 1; i < n; ++i) {
    if (r[i].l <= ed) {
      ed = max(ed, r[i].r);
    } else {
      res.push_back({st, ed});
      st = r[i].l, ed = r[i].r;
    }
  }
  res.push_back({st, ed});
  cout << res.size() << endl;
}
