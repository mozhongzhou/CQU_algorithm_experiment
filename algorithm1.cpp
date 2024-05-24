#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 函数用于找出数组中的所有众数和重数
void findModesAndCount(const vector<int> &nums, vector<int> &modes, int &count)
{
    modes.clear();
    modes.push_back(nums[0]);
    count = 1;
    int curNum = nums[0];
    int curCount = 1;
    for (int i = 1; i < nums.size(); i++)
    {
        if (nums[i] == curNum)
        {
            curCount++;
        }
        else
        {
            if (curCount > count)
            {
                modes.clear();
                modes.push_back(curNum);
                count = curCount;
            }
            else if (curCount == count && find(modes.begin(), modes.end(), curNum) == modes.end())
            {
                modes.push_back(curNum);
            }
            curNum = nums[i];
            curCount = 1;
        }
    }
    if (curCount > count)
    {
        modes.clear();
        modes.push_back(curNum);
        count = curCount;
    }
    else if (curCount == count && find(modes.begin(), modes.end(), curNum) == modes.end())
    {
        modes.push_back(curNum);
    }
}

int main()
{
    // 测试案例
    vector<vector<int>> testCases = {
        {1, 2, 2, 2, 2, 3, 3, 5, 6, 6, 6, 6},
        {1, 1, 2, 2, 2, 3, 3, 3, 3},
        {1},
        {1, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 4}};

    for (const auto &nums : testCases)
    {
        vector<int> modes;
        int count;
        findModesAndCount(nums, modes, count);
        cout << "数组：";
        for (int num : nums)
        {
            cout << num << " ";
        }
        cout << "\n众数：";
        for (int mode : modes)
        {
            cout << mode << " ";
        }
        cout << "，重数：" << count << "\n\n";
    }

    return 0;
}