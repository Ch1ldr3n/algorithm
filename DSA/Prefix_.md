题目描述

给定一个字符串 S[1..n]，定义前缀 prefix[i] = S[1..i]，现在想知道所有 prefix[i] 在S中出现的次数总和，一次出现定义为 $$prefix[i]==s[j..j+i-1]$$

所使用数据结构与算法的构思、原理和实现要点

采用kmp算法中的next数组辅助求解：

第一步求出next数组

第二步在next数组的基础上进行动态规划：

定义位置i的next链：i, next[i], next[next[i]], ..., 0 (对于next[0]=-1，特殊定义0的next链长度为0)

则有以下结论：

$$prefix[i]==s[j-i+1..j] \leftrightarrow i \in next_seq(j)$$

大致证明如下：

$prefix[i]==s[j-i+1..j] \rightarrow i \in next_seq(j)$

假设$i \notin next_seq(j)$，因为$i<j$，这必然是因为存在某个$x \in next_seq(j)$，且$i<x$，且$next[x]<i$，这就是说$prefix[i] \ne s[x-i+1..x]$(否则$next[x]\ge i$)，而沿着$next_seq$往回走(定义$prev[x]$为$x$在$next_seq$上的前驱)，有$s[x-i+1,x]=s[prev[x]-i+1..prev[x]]=s[prev[prev[x]]-i+1..prev[prev[x]]]=...=s[j-i+1..j]$，从而$prefix[i] \ne s[j-i+1..j]$，矛盾

$prefix[i]==s[j-i+1..j] \leftarrow i \in next_seq(j)$

沿用上面$prev[x]$的定义，有$prefix[i]=s[prev[i]-i+1..prev[i]]=s[prev[prev[i]]-i+1..prev[prev[i]]]=...=s[j-i+1..j]$

因此这个结论成立

从而，任何一个前缀出现一次都会且仅会给某一个$next_seq$贡献长度$1$，因此最终答案就是所有$next_seq$的长度总和。这可以用动态规划来计算： $$dp[0]=0; dp[i]=dp[next[i]]+1$$ $$ans=\sum dp$$

完成过程中遇到的问题，排除问题的主要过程、使用的方法和技巧，以及参考资料

没有问题

本题使用了两个常数优化技巧：

读入字符串时采用linux的系统函数mmap，这达到了超过fread的效率，更不必说与setvbuf之类的效果相当一般的读入优化比

经分析发现，实际上不需要dp和next这两个数组，这是因为当dp[0...i]被计算出来之后，不再需要next[0...i]，因此可以将二者合并成一个数组，空间节省近一半，且因空间局部性更好，时间效率也会略有上升。此时的状态转移方程应修改为 $$next[i]=next[next[i]]+1$$

时间和空间复杂度的估算

计算next数组耗时$O(n)$，在next数组上dp耗时$O(n)$，总耗时$O(n)$

存储原串消耗空间$O(n)$，next数组消耗空间$O(n)$，总空间$O(n)$

实际效果

将fread换成mmap取得了20ms左右的加速，将dp数组与next数组合并取得了20ms左右的加速，这都符合我的预计。

当撰写这篇报告时，PA排行榜上暂列第一。