#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

void merge(vector<pii> &segs) {
  vector<pii> res;
  sort(segs.begin(), segs.end());

  int st = segs[0].first, ed = segs[0].second;
  for (int i = 1; i < segs.size(); ++i) {
    if (segs[i].first <= ed) {
      ed = max(ed, segs[i].second);
    } else {
      res.push_back({st, ed});
      st = segs[i].first, ed = segs[i].second;
    }
  }
  res.push_back({st, ed});
  segs = res;
}

int main() {
  vector<pii> segs;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    segs.push_back({l, r});
  }
  merge(segs);
  cout << segs.size() << endl;
}