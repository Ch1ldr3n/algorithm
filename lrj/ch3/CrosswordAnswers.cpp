#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int kase;
struct Point {
  int x, y;
  Point(int x = 0, int y = 0) : x(x), y(y) {}
};
Point operator+(const Point& a, const Point& b) {
  return Point(a.x + b.x, a.y + b.y);
}

vector<string> grid;
int r, c;
bool valid(const Point& p) {
  return p.x >= 0 && p.x < r && p.y >= 0 && p.y < c;
}

int main() {
  //   freopen("input.txt", "r", stdin);
  //   freopen("output.txt", "w", stdout);
  Point dUp(-1, 0), dLeft(0, -1), dRight(0, 1), dDown(1, 0);
  while (cin >> r && r) {
    cin >> c;
    grid.clear();
    string line;
    vector<int> across, down;
    vector<Point> eligible;
    for (int i = 0; i < r; ++i) {
      cin >> line;
      grid.push_back(line);
      for (int j = 0; j < c; ++j) {
        if (line[j] == '*') continue;
        Point p(i, j), left = p + dLeft, up = p + dUp;
        bool isAcross = !valid(left) || grid[left.x][left.y] == '*';
        bool isDown = !valid(up) || grid[up.x][up.y] == '*';
        if (isAcross) across.push_back(eligible.size());
        if (isDown) down.push_back(eligible.size());
        if (isAcross || isDown) eligible.push_back(p);
      }
    }
    if (kase > 0) puts("");
    cout << "puzzle #" << ++kase << ":" << endl;
    puts("Across");
    char buf[15];
    int bufLen;
    for (auto a : across) {
      memset(buf, 0, sizeof(buf));
      bufLen = 0;
      auto p = eligible[a];
      while (valid(p) && grid[p.x][p.y] != '*') {
        buf[bufLen++] = grid[p.x][p.y];
        p = p + dRight;
      }
      printf("%3d.%s\n", a + 1, buf);
    }
    puts("Down");
    for (auto d : down) {
      memset(buf, 0, sizeof(buf));
      bufLen = 0;
      auto p = eligible[d];
      while (valid(p) && grid[p.x][p.y] != '*') {
        buf[bufLen++] = grid[p.x][p.y];
        p = p + dDown;
      }
      printf("%3d.%s\n", d + 1, buf);
    }
  }
  return 0;
}
