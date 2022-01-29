#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n, m;
const int maxn = 100010;
vector<int> pos;
vector<pair<int, int>> add, query;
int a[maxn * 3], s[maxn * 3];

int find(int u) {
  int l = 0, r = pos.size() - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (pos[mid] >= u)
      r = mid;
    else
      l = mid + 1;
  }
  return l + 1;
}

vector<int>::iterator unique(vector<int>& a) {
  int j = 0;
  for (int i = 1; i < a.size(); ++i) {
    if (a[i] != a[j]) a[++j] = a[i];
  }
  return a.begin() + j + 1;
}

int main() {
  cin >> n >> m;
  while (n--) {
    int x, c;
    cin >> x >> c;
    pos.push_back(x);
    add.push_back({x, c});
  }
  while (m--) {
    int l, r;
    cin >> l >> r;
    pos.push_back(l);
    pos.push_back(r);
    query.push_back({l, r});
  }
  sort(pos.begin(), pos.end());
  pos.erase(unique(pos), pos.end());
  for (auto i : add) {
    a[find(i.first)] += i.second;
  }
  for (int i = 1; i <= pos.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  for (auto q : query) {
    cout << s[find(q.second)] - s[find(q.first) - 1] << endl;
  }
}