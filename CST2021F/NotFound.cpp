#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = (16777216 >> 3) + 10;
// 创建一个无符号字符串数组来存储输入数据
// 其中，一个char存8个字符
unsigned char a[N];

// 获得输入字符串原本的第u位
inline int get(int u)
{
    int idx = u >> 3;
    int remain = u & 7;
    int tmp = (int)a[idx];
    // 取tmp的右数第8-remain位
    return (tmp >> (7 - remain)) & 1;
}

// 获得01串a的[l, r)子串对应的int值
int get_value(int l, int r)
{
    // 找到对应的a的index
    int hi = r >> 3;
    int lo = l >> 3;

    if (hi - lo >= 2)
    {
        int val = 0;
        // 此时一定可以分为3部分 [l, lo + 1) [lo + 1, hi) [hi, r)
        for (int i = l; i < ((lo + 1) << 3); ++i) val = (val << 1) + get(i);
        for (int i = lo + 1; i < hi; ++i) val = (val << 8) + a[i];
        int remain = r & 7;
        val = (val << remain) + (a[hi] >> (8 - remain));
        return val; 
    }
    else
    {
        int val = 0;
        // 直接遍历这之间的所有元素
        for (int i = l; i < r; ++i) val = (val << 1) + get(i);
        return val;
    }
}

// 位图的检测元素是否存在，来源：“讲义Bitmap”
inline bool test(unsigned char * bm, int k)
{
    return bm[k >> 3] & (0x80 >> (k & 0x07));
}

// 位图的添加元素，来源：讲义“Bitmap”
void set(unsigned char * bm, int k)
{
    bm[k >> 3] |= (0x80 >> (k & 0x07));
}

int main()
{

    // 读入数据，进行转换
    unsigned char newchar;
    unsigned char t = '\0'; // 中间值
    int tlen = 0; // 标记中间值长度，看是否为8
    int idx = 0; // 当前存到哪一位
    int alen = 0; // a的长度(01串的总长度)
    while (true)
    {
        newchar = getchar();
        if (newchar == '\n') break;
        alen ++;
        t = (t << 1) + (newchar - '0');
        tlen++;
        if (tlen == 8)
        {
            a[idx++] = t;
            tlen = 0;
            t = '\0';
        }
    }
    if (t != '\0')
    {
        while (tlen < 8)
        {
            t = t << 1;
            tlen ++;
        }
        a[idx++] = t;
    }
    
    int anslen = 1; // 答案串的长度，从1开始遍历
    bool flag = true; // 区分答案串较短还是较长
    int ans[3]; // 储存答案
    idx = 0; // 下标
    memset(ans, 0, sizeof ans); // 初始化答案
    // 遍历答案长度：当答案长度不太长时，枚举所有情况；
    // 当答案长度较长时，枚举到log(n)即可
    while ((flag ? (anslen <= alen) : ((1 << anslen) <= alen)))
    {
        unsigned char bm[((1 << anslen) + 7) >> 3];
        memset(bm, 0, sizeof bm);
        // 从[0,k)遍历到[n-k,n)
        int res = 0;
        for (int i = 0; i + anslen <= alen; ++i)
        {
            int val = get_value(i, i + anslen);
            // 如果有新的子串，记录下来
            if (!test(bm, val)) res++;
            // 将这个子串放入位图
            set(bm, val);
            // 当不同子串数等于2^答案长度时，可以断定此答案长度下没有解。
            if (res == (1 << anslen)) break;
        }

        if (res == (1 << anslen)) // 可能是这里出错了。
            idx = 0;
        else
        {
            for (int i = 0; i < (1 << anslen); ++i)
            {
                // 找到字典序最小的，满足条件的解。
                if (!test(bm, i))
                {
                    ans[idx++] = i;
                    ans[idx++] = anslen;
                    ans[idx++] = 1;
                    break;
                }
            }   
        }
        if (ans[2] == 1) break;
        // 更新循环的控制变量
        anslen++;
        if (anslen <= 4) flag = true;
        else flag = false;
    }
    
    // 输出答案串
    for (int i = ans[1]; i >= 1; --i)
    {
        printf("%d", (ans[0] >> (i - 1)) & 1);
    }   
    printf("\n"); 

    return 0;
}