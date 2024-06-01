#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

bool is_valid(int grid[3][3], int r, int c, int num)
{
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (auto &dir : directions)
    {
        int nr = r + dir[0], nc = c + dir[1];
        if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3 && grid[nr][nc] != 0)
        {
            if (!is_prime(grid[nr][nc] + num))
            {
                return false;
            }
        }
    }
    return true;
}

void print_grid(int grid[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void solve(int grid[3][3], std::vector<int> &nums, int idx, int &count)
{
    if (idx == 9)
    {
        ++count;
        print_grid(grid);
        return;
    }

    int r = idx / 3;
    int c = idx % 3;

    for (int i = 0; i < nums.size(); ++i)
    {
        int num = nums[i];
        if (is_valid(grid, r, c, num))
        {
            grid[r][c] = num;
            nums.erase(nums.begin() + i);
            solve(grid, nums, idx + 1, count);
            nums.insert(nums.begin() + i, num);
            grid[r][c] = 0;
        }
    }
}

int main()
{
    int grid[3][3] = {0};
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int count = 0;
    for (int i = 0; i < nums.size(); ++i)
    {
        int num = nums[i];
        std::vector<int> remaining_nums(nums.begin(), nums.end());
        remaining_nums.erase(remaining_nums.begin() + i);
        grid[0][0] = num;
        solve(grid, remaining_nums, 1, count);
        grid[0][0] = 0;
    }

    std::cout << "Number of valid grids: " << count << std::endl;

    return 0;
}
