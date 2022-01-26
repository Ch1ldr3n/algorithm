# 题目描述
求给定字符串S所有前缀在S中出现次数之和

## 所使用数据结构与算法的构思、原理和实现要点

本题利用了KMP算法中next数组的含义，利用next数组来辅助计数。next[j]的含义是使前缀S[0,t)和后缀S[j-t,j)相同的最大的t，也即使这个相同的部分最长。

定义j处的next链：j, next[j],next[next[j]], ..., 0;

因此如果prefix[i] = S[x-i+1...x]，则i一定出现在x处的next链中。因此任何前缀在字符串S中出现一次，都对某一处的next链的长度贡献为1.于是所有前缀在串中出现的次数是所有next链的长度之和。

如何求解这个值呢？首先0处的next链长度为0，其次有递推关系: next[x]处的next链长度 = x处的next链长度+1.因此可以使用动态规划求解每一处的next链长度。

## 困难及其解决
本题思路十分精妙，我参考了答疑坊同学的讲解才理解这个思路。

## 复杂度分析
时间复杂度O(n).
空间复杂度O(n).