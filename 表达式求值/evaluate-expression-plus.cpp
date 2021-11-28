#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<char, int> pri = { { '+', 1 }, { '-', 1 }, { '*', 2 }, { '/', 2 }, { '^', 3 }, { '!', 4 } };

void eval(stack<int>& num, stack<char>& op)
{
    char ch = op.top();
    op.pop();
    if (ch == '!') {
        int a = num.top();
        num.pop();
        int fac = 1;
        while (a)
            fac *= a--;
    } else {
        int b = num.top();
        num.pop();
        int a = num.top();
        num.pop();
        int c;
        switch (ch) {
        case '+':
            c = a + b;
            break;
        case '-':
            c = a - b;
            break;
        case '*':
            c = a * b;
            break;
        case '/':
            c = a / b;
            break;
        case '^':
            c = 1;
            while (b--)
                c *= a;
            break;
        default:
            break;
        }
        num.push(c);
    }
}
int evaluate(string s)
{
    stack<int> num;
    stack<char> op;
    for (int i = 0, n = s.size(); i < n; ++i) {
        if (isdigit(s[i])) { //读取操作数 233+4*3^2
            int x = 0, j = i;
            while (j < n && isdigit(s[j])) {
                x = x * 10 + (s[j++] - '0');
            }
            num.push(x);
            i = j - 1;
        } else if (s[i] == '(') {
            op.push(s[i]);
        } else if (s[i] == ')') {
            while (op.top() != '(') { //处理左右括号之间的所有计算
                eval(num, op);
            }
            op.pop(); //弹出左括号
        } else {
            while (op.size() && pri[op.top()] >= pri[s[i]]) {
                eval(num, op);
            }
            op.push(s[i]);
        }
    }
    while (op.size()) {
        eval(num, op);
    }
    return num.top();
}

int main()
{
    string s;
    cin >> s;
    cout << evaluate(s) << endl;
}