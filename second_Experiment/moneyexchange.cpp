#include <stdio.h>

// 函数solve用于找出所有可能的兑换方式
void solve(int n)
{
    int x, y, z;   // x, y, z分别表示1分、2分和5分硬币的数量
    int count = 0; // count用于计数所有可能的兑换方式

    // 遍历所有可能的5分硬币的数量
    for (z = 0; z <= n / 5; z++)
    {
        int remaining = n - 5 * z; // 计算剩余的金额

        // 遍历所有可能的2分硬币的数量
        for (y = 0; y <= remaining / 2; y++)
        {
            x = remaining - 2 * y; // 直接计算1分硬币的数量

            // 打印出这种兑换方式
            printf("兑法%d: ", ++count);
            if (z != 0)
                printf("5分硬币%d个 ", z);
            if (y != 0)
                printf("2分硬币%d个 ", y);
            if (x != 0)
                printf("1分硬币%d个 ", x);
            printf("\n");
        }
    }

    // 打印出总的兑换方式数量
    printf("共有%d种兑法\n", count);
}

int main()
{
    int n; // n表示要兑换的金额

    // 从用户那里获取要兑换的金额
    printf("请输入要兑换的钱数: ");
    scanf("%d", &n);

    // 调用solve函数来找出所有可能的兑换方式
    solve(n);

    return 0;
}