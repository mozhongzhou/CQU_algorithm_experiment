
#include <iostream>
#include <vector>

// 检查当前组合是否满足条件
bool check(int a, int b, int c, int d, int e)
{
    return a * b - c * d - e == 1;
}

// 深度优先搜索
void dfs(std::vector<int> &nums, std::vector<bool> &used, std::vector<int> &path)
{
    if (path.size() == 5)
    {
        if (check(path[0], path[1], path[2], path[3], path[4]))
        {
            std::cout << "a=" << path[0] << ", b=" << path[1] << ", c=" << path[2] << ", d=" << path[3] << ", e=" << path[4] << std::endl;
        }
        return;
    }
    for (int i = 0; i < 5; i++)
    {
        if (!used[i])
        {
            used[i] = true;
            path.push_back(nums[i]);
            dfs(nums, used, path);
            used[i] = false;
            path.pop_back();
        }
    }
}

int main()
{
    std::vector<int> nums = {1, 2, 3, 4, 5}; // 所有可能的取值
    std::vector<bool> used(5, false);        // 标记某个值是否已经被使用
    std::vector<int> path;                   // 存储当前的组合
    dfs(nums, used, path);                   // 开始搜索
    return 0;
}
