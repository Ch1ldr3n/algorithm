#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int cnt[26]; // 统计每个字母出现的次数
int sum; // 出现的字符总数
bool appear[26]; // 记录字符是否出现
typedef pair<int, char> PII;
int stack[110], top = -1;
int len[26]; // 记录每个字母的编码长度
void push(int u)
{
    stack[++top] = u;
}
int pop()
{
    return stack[top--];
}
void del()
{
    top = -1;
}
int length()
{
    return top + 1;
}
void print()
{
    for (int i = 0; i <= top; ++i)
    {
        printf("%d", stack[i]);
    }
    printf("\n");
}

struct node
{
    PII data;
    node * lc; // 左儿子
    node * rc; // 右儿子
    node * nxt;
    node * pre;

    node()
    {
        lc = rc = nullptr;
        nxt = pre = nullptr;
    }
    node(node * _lc, node * _rc)
    {
        lc = _lc, rc = _rc;
        data.first = lc->data.first + rc->data.first;
        data.second = '^';
    }

    node(int count, char ch)
    {
        data.first = count;
        data.second = ch;
        lc = rc = nullptr;
    }
};

struct queue
{
    node * head;
    node * tail;

    queue()
    {
        head = new node();
        tail = new node();
        head->nxt = tail;
        tail->pre = head;
    }
    bool empty()
    {
        return head->nxt == tail && tail->pre == head;
    }
    void push(node * tmp)
    {
        if (empty())
        {
            head->nxt = tmp;
            tmp->nxt = tail;
            tail->pre = tmp;
            tmp->pre = head;
        }
        else
        {
            // 维护从小到大的有序性
            node * cmp = tail->pre;
            while (cmp != head)
            {
                // 找到第一个<=tmp的点，插在它后面
                if (tmp->data.first >= cmp->data.first) break;
                cmp = cmp->pre;
            }
            tmp->nxt = cmp->nxt;
            tmp->pre = cmp;
            cmp->nxt->pre = tmp;
            cmp->nxt = tmp;
        }
    }
    node * pop()
    {
        node * tmp = head->nxt;
        head->nxt = tmp->nxt;
        tmp->nxt->pre = head;
        return tmp;
    }
};

void show()
{
    cout << "字符总数：" << sum << endl;
    for (int i = 0; i < 26; ++i) 
        if (appear[i])
            cout << (char)('a' + i) << ": " << cnt[i] << endl;
}

void dfs(node * n)
{
    // 如果是叶子节点，计算长度
    if (n->data.second != '^')
    {
        len[(int)(n->data.second - 'a')] = length();
    }
    else
    {
        push(0);
        dfs(n->lc);
        pop();

        push(1);
        dfs(n->rc);
        pop();
    }
}

void dfss(node * n)
{
    if (n->data.second != '^')
    {
        printf("%c ", n->data.second);
        print();
    }
    else
    {
        push(0);
        dfss(n->lc);
        pop();
        push(1);
        dfss(n->rc);
        pop();
    }
}

int main()
{
    // 统计频率
    char c;
    while (true)
    {
        c = getchar();
        if (c < 'a' || c > 'z') break;
        // 处理字符
        int id = c - 'a';
        if (!appear[id])
        {
            appear[id] = true;
            sum++;
        }
        cnt[id]++;
    }

    queue q;
    // 创建26或更少个子树，并存入优先级队列
    for (int i = 0; i < 26; ++i)
    {
        if (appear[i])
        {
            node * tmp = new node(cnt[i], ('a' + i));
            q.push(tmp);
        }
    }
    
    // 构造huffman树
    while (true)
    {
        node * a = q.pop();
        node * b = q.pop();
        node * tmp = new node(a, b);
        if (q.empty())
        {
            q.push(tmp);
            break;
        }
        else
        {
            q.push(tmp);
        }
    }

    node * root = q.pop(); // 根节点

    // dfs遍历huffman树，计算编码长度
    dfs(root);
    int total = 0;
    int i = 0;
    while (i < 26)
    {
        if (appear[i])
        {
            total += len[i] * cnt[i];
        }
        ++i;
    }
    printf("%d\n", total);

    dfss(root);
    // show();
    return 0;
}