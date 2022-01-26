#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int kase;
struct Vector {
  int x, y;
  Vector(int x = 0, int y = 0) : x(x), y(y) {}
};

Vector operator+(const Vector& a, const Vector& b) {
  return Vector(a.x + b.x, a.y + b.y);
}
Vector operator-(const Vector& a, const Vector& b) {
  return Vector(a.x - b.x, a.y - b.y);
}
Vector operator*(const Vector& a, int p) { return Vector(a.x * p, a.y * p); }
Vector operator/(const Vector& a, int p) { return Vector(a.x / p, a.y / p); }
bool operator==(const Vector& a, const Vector& b) {
  return a.x == b.x && a.y == b.y;
}
bool operator<(const Vector& a, const Vector& b) {
  return a.x < b.x || a.x == b.x && a.y < b.y;
}

vector<string> grid;
Vector ePos;
const int gSize = 5;
void printGrid() {
  for (int i = 0; i < gSize; i++) {
    for (int j = 0; j < gSize; j++) {
      if (j) cout << " ";
      cout << grid[i][j];
    }
    cout << endl;
  }
}

map<char, Vector> dirs{
    {'A', Vector(-1, 0)},
    {'B', Vector(1, 0)},
    {'L', Vector(0, -1)},
    {'R', Vector(0, 1)},
};

bool valid(const Vector& p) {
  return p.x >= 0 && p.x < gSize && p.y >= 0 && p.y < gSize;
}

bool tryMove(char cmd) {
  if (!dirs.count(cmd)) return false;
  auto delta = dirs[cmd];
  auto nPos = ePos + delta;
  if (!valid(nPos)) return false;
  swap(grid[nPos.x][nPos.y], grid[ePos.x][ePos.y]);
  ePos = nPos;
  return true;
}

int main() {
  //   freopen("input.txt", "r", stdin);
  //   freopen("output.txt", "w", stdout);
  string line;
  while (1) {
    // 初始化
    grid.clear();
    ePos.x = ePos.y = -1;
    // 读入棋盘
    for (int i = 0; i < gSize; ++i) {
      getline(cin, line);
      if (line == "Z") return 0;
      for (int j = 0; j < gSize; ++j) {
        if (line[j] == ' ') {
          ePos.x = i, ePos.y = j;
        }
      }
      grid.push_back(line);
    }
    // 读入操作
    string moves;
    while (1) {
      getline(cin, line);
      if (*line.rbegin() == '0') {
        moves.append(line, 0, line.size() - 1);
        break;
      } else
        moves.append(line);
    }
    bool legal = true;
    for (const auto& m : moves)
      if (!tryMove(m)) {
        legal = false;
        break;
      }

    if (kase >= 1) cout << endl;
    printf("Puzzle #%d:\n", ++kase);
    if (legal)
      printGrid();
    else
      cout << "This puzzle has no final configuration." << endl;
  }
}
