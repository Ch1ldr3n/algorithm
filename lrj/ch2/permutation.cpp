#include <cstdio>
int main()
{
    /*
      abc, def, ghi   1:2:3
      估算abc的范围应该是123～max。因为ghi最大取987，max=987/3=329
      遍历大约两百个数，判断是否满足要求
    */
    for (int abc = 123; abc <= 329; ++abc) {
        int def = 2 * abc, ghi = 3 * abc;
        int a = abc / 100, b = (abc / 10) % 10, c = abc % 10;
        int d = def / 100, e = (def / 10) % 10, f = def % 10;
        int g = ghi / 100, h = (ghi / 10) % 10, i = ghi % 10;
        if (a + b + c + d + e + f + g + h + i == 45 && a * b * c * d * e * f * g * h * i == 362880)
            //判断是否各个数字只出现了一次
            printf("%d %d %d\n", abc, def, ghi);
    }
}