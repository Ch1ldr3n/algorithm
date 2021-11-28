/*
中缀表达式求值
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

stack<int> num;
stack<char> op;

void eval()
{
    int a = num.top(); //第二个操作数
    num.pop();

    int b = num.top(); //第一个操作数
    num.pop();

    char p = op.top(); //运算符
    op.pop();

    int r = 0; //结果

    //计算结果
    if (p == '+')
        r = b + a;
    if (p == '-')
        r = b - a;
    if (p == '*')
        r = b * a;
    if (p == '/')
        r = b / a;

    num.push(r); //结果入栈
}

int main()
{
    unordered_map<char, int> pri {
        { '+', 1 }, { '-', 1 }, { '*', 2 }, { '/', 2 }
    };

    string s;
    cin >> s;

    for (int i = 0; i < s.size(); ++i) {
        if (isdigit(s[i])) {
            int x = 0, j = i;
            while (j < s.size() && isdigit(s[j])) {
                x = x * 10 + (s[j] - '0');
                j++;
            }
            num.push(x);
            i = j - 1;
        } else if (s[i] == '(') {
            op.push(s[i]);
        } else if (s[i] == ')') {
            while (op.top() != '(')
                eval();
            op.pop();
        } else {
            while (op.size() && pri[op.top()] >= pri[s[i]])
                eval();
            op.push(s[i]);
        }
    }
    while (op.size())
        eval();
    cout << num.top() << endl;
    return 0;
}