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

int find2(int u) {
  int l = 0, r = pos.size() - 1;
  while (l < r) {
    int mid = l + r + 1 >> 1;
    if (pos[mid] <= u)
      l = mid;
    else
      r = mid - 1;
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
  sort(pos.begin(), pos.end());
  pos.erase(unique(pos), pos.end());
  for (auto i : add) {
    a[find(i.first)] += i.second;
  }
  for (int i = 1; i <= pos.size(); ++i) {
    s[i] = s[i - 1] + a[i];
  }

  while (m--) {
    int l, r;
    cin >> l >> r;
    l = find(l), r = find2(r);
    cout << s[r] - s[l - 1] << endl;
  }
  //  bug ： 输入范围之外的区间，输出非0；
}