#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

int evalRPN(vector<string>& tokens)
{
    stack<int> nums;
    for (auto& token : tokens) {
        if (isdigit(token[token.size() - 1])) {
            nums.push(stoi(token));
        } else {
            int b = nums.top();
            nums.pop();
            int a = nums.top();
            nums.pop();
            int c = 0;
            switch (token[0]) {
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
            }
            nums.push(c);
        }
    }
    return nums.top();
}

int main()
{
    return 0;
}