class MinStack {
    stack<int> stk; //正常栈 <a_1, a_2, ..., a_n]
    stack<int> min_stk; //每个元素都对应正常栈以该元素为起点的后缀里的最小值 b_k = min_of(a_k ~ a_n).
    // 这样最小元素即为min_stk.top(), O(1)

public:
    MinStack()
    {
        min_stk.push(__INT_MAX__);
    }

    void push(int val)
    {
        stk.push(val);
        min_stk.push(min(val, min_stk.top()));
    }

    void pop()
    {
        stk.pop();
        min_stk.pop();
    }

    int top()
    {
        return stk.top();
    }

    int getMin()
    {
        return min_stk.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main()
{
}