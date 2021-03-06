# 2-2 Not Found

## 数据结构和算法设计

**1. 思路**

根据提示知道本题需要使用位图。同时时间空间要求都很高，因此需要尽可能的优化时间和空间复杂度，主要是空间，可以使用状态压缩来实现。

**2 .算法和数据结构设计**

由于空间限制到6MB左右，输入数据都会超出这个限制。由于每个unsigned char有1个字节8个比特，所以考虑每个char存储8个输入数据的信息。通过状态压缩，得到数组a。当答案长度不太大时，枚举这些长度。对于每个长度，用位图来存储原字符串的所有不同的子串。同时注意到每个答案长度，最多只有2^n个不同的串，因此当位图里存入的不同的子串达到上限时，可以提前终止循环。

## 完成过程中遇到的问题

【参考资料】

讲义：Bitmap

## 时空复杂度的估算

1.  时间复杂度

压缩：O(输入字符串长度)

对答案长度的枚举不会超过24，因次外层循环为O(1)。内层循环中辅助函数均可认为是O(1)，但本身仍有O(logn)的复杂度。

因此总的时间复杂度为O(logn)

2.  空间复杂度

O(输入字符串长度)