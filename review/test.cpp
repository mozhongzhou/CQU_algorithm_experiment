#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int maxSubArray(std::vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;

    std::vector<int> dp(n);
    dp[0] = nums[0];
    int max_sum = dp[0];

    for (int i = 1; i < n; i++)
    {
        dp[i] = std::max(nums[i], dp[i - 1] + nums[i]);
        cout << "dp[" << i << "] = " << dp[i] << endl;
        max_sum = std::max(max_sum, dp[i]);
        cout << "max_sum = " << max_sum << endl;
    }

    return max_sum;
}
int main()
{
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "The maximum subarray sum is: " << maxSubArray(nums) << std::endl;
    return 0;
}