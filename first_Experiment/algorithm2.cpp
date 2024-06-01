#include <stdio.h>

int Partition(int a[], int low, int high)
{
    int i = low, j = high;
    int povit = a[low];
    while (i < j)
    {
        while (i < j && a[j] >= povit)
            j--;
        a[i] = a[j];
        while (i < j && a[i] <= povit)
            i++;
        a[j] = a[i];
    }
    a[i] = povit;
    return i;
}

int Solve(int a[], int n, int &pivot)
{
    int low = 0, high = n - 1;
    bool flag = true;
    while (flag)
    {
        int i = Partition(a, low, high);
        if (i == n / 2 - 1)
        {
            flag = false;
            pivot = a[i];
        }
        else if (i < n / 2 - 1)
            low = i + 1;
        else
            high = i - 1;
    }
    int s1 = 0, s2 = 0;
    printf("\n子数组1:");
    for (int i = 0; i < n / 2; i++)
    {
        s1 += a[i];
        printf("%3d", a[i]);
    }
    printf("\n子数组2:");
    for (int j = n / 2; j < n; j++)
    {
        s2 += a[j];
        printf("%3d", a[j]);
    }
    return s2 - s1;
}

int main()
{
    printf("实验结果:\n");

    int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8};
    int n = sizeof(a) / sizeof(a[0]);
    printf("初始序列:");
    for (int i = 0; i < n; i++)
        printf("%3d", a[i]);
    int pivot;
    int result = Solve(a, n, pivot);
    printf("\n求解结果%d，划分点%d\n", result, pivot);

    int b[] = {1, 3, 5, 7, 9, 10, 2, 4, 6, 8};
    int m = sizeof(b) / sizeof(b[0]);
    printf("初始序列:");
    for (int i = 0; i < m; i++)
        printf("%3d", b[i]);
    result = Solve(b, m, pivot);
    printf("\n求解结果%d，划分点%d\n", result, pivot);
}