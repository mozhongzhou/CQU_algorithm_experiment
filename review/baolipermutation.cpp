#include <vector>
#include <iostream>

void generatePermutations(std::vector<int> &currentPermutation, std::vector<int> &remainingElements, std::vector<std::vector<int>> &result)
{
    if (remainingElements.empty())
    {
        // 当没有剩余元素时，将当前排列添加到结果中
        result.push_back(currentPermutation);
        return;
    }

    for (int i = 0; i < remainingElements.size(); ++i)
    {
        // 选择当前元素
        int element = remainingElements[i];
        currentPermutation.push_back(element);

        // 移除当前元素，准备下一次递归
        remainingElements.erase(remainingElements.begin() + i);

        // 递归调用
        generatePermutations(currentPermutation, remainingElements, result);

        // 回溯，撤销选择
        currentPermutation.pop_back();
        remainingElements.insert(remainingElements.begin() + i, element);
    }
}

int main()
{
    std::vector<int> elements = {1, 2, 3}; // 示例元素集
    std::vector<int> currentPermutation;
    std::vector<std::vector<int>> result;

    generatePermutations(currentPermutation, elements, result);

    // 打印所有排列
    for (const auto &permutation : result)
    {
        for (int num : permutation)
        {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }

    return 0;
}