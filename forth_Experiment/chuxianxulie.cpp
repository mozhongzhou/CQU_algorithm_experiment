#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main()
{
    int n;
    std::cin >> n; // 读取数字个数
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> nums[i]; // 读取每个数字
    }

    std::unordered_map<int, int> countMap; // 用于存储每个数字及其出现次数
    for (int num : nums)
    {
        ++countMap[num]; // 计算每个数字的出现次数
    }

    int maxCount = 0; // 出现次数最多的次数
    int result = 0;   // 出现次数最多的数
    for (const auto &pair : countMap)
    {
        if (pair.second > maxCount || (pair.second == maxCount && pair.first < result))
        {
            maxCount = pair.second;
            result = pair.first;
        }
    }

    std::cout << result << std::endl; // 输出结果
    return 0;
}