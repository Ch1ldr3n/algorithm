# 整数二分

二分的本质：

找到一个性质使序列一分为二，一半满足这个性质，一半不满足这个性质。那么二分查找可以求得左区间的右端点，和右区间的左端点。

$$[l, ...,red, green, ..., r]$$

$[l, red]$是红色区间，red代表其右端点；$[green, r]$是绿色区间，green代表其左端点。

二分查找可以在$log(n)$时间内找到red或green

**一、找red**

`mid = ?`

`if(check(mid))`  说明mid此时落在红色区间内，则查找区间缩小为$[mid, r]$

`else` 说明mid此时落在绿色区间内，则查找区间缩小为$[l, mid-1]$

**二、找green**

`mid = ?`

`if(check(mid))` 说明mid此时落在绿色区间内，则查找区间缩小为$[l, mid]$

`else` 说明mid此时落在红色区间内，则查找区间缩小为$[mid + 1, r]$

---

问题在于这两个问号，只是简单地取`mid=l+r>>1`就可以了吗？

这是经典的边界问题，在快排模板里也出现过。第一种情况里，$[l, r] \rArr [mid, r]$，则mid不能取到$l$，否则会陷入死循环。同理，第二种情况$mid$不能取到$r$。

综上，第一个问号`mid = l + r + 1 >> 1`， 第二个问号`mid = l + r >> 1`


```
模板

bool check(int x) {/* ... */} // 检查x是否满足某种性质

// 区间[l, r]被划分成[l, mid]和[mid + 1, r]时使用：
int bsearch_1(int l, int r)
{
    while (l < r)
    {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;    // check()判断mid是否满足性质
        else l = mid + 1;
    }
    return l;
}
// 区间[l, r]被划分成[l, mid - 1]和[mid, r]时使用：
int bsearch_2(int l, int r)
{
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

```