#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<char, int> pr{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

stack<int> num;
stack<char> op;

void eval() {
  auto b = num.top();
  num.pop();
  auto a = num.top();
  num.pop();
  auto c = op.top();
  op.pop();
  int x;
  if (c == '+')
    x = a + b;
  else if (c == '-')
    x = a - b;
  else if (c == '*')
    x = a * b;
  else
    x = a / b;
  num.push(x);
}

int main() {
  string exp;
  cin >> exp;
  for (int i = 0; i < exp.size(); ++i) {
    auto c = exp[i];
    if (isdigit(c)) {
      int sum = 0, j;
      for (j = i; isdigit(exp[j]) && j < exp.size(); j++) {
        sum = sum * 10 + (exp[j] - '0');
      }
      i = j - 1;
      num.push(sum);
    } else if (c == '(')
      op.push(c);
    else if (c == ')') {
      while (op.top() != '(') eval();
      op.pop();
    } else {
      while (op.size() && pr[op.top()] >= pr[c]) eval();
      op.push(c);
    }
  }
  while (op.size()) eval();
  cout << num.top() << endl;
}