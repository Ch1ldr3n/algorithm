#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void searchRoot(double u) {
  double l = -100, r = 100;
  while (r - l > 1e-8) {
    double mid = (l + r) / 2;
    if (mid * mid * mid >= u)
      r = mid;
    else
      l = mid;
  }
  printf("%.6lf\n", l);
}

int main() {
  double n;
  cin >> n;
  searchRoot(n);
}