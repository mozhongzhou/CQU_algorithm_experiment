#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node
{
    int level;             // 当前处理到的行（人）
    int cost;              // 到目前为止的成本
    vector<bool> assigned; // 标记任务是否已被分配
};

// 自定义优先队列比较函数，优先级高的是成本低的
auto cmp = [](const Node &left, const Node &right)
{ return left.cost > right.cost; };
priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
// 修改后的lowerBound函数，增加输出细节
int lowerBound(const Node &node, const vector<vector<int>> &costMatrix)
{
    int lb = node.cost;
    int n = costMatrix.size();
    cout << "计算下界，当前成本: " << node.cost << ", 未分配任务的最小成本: ";
    for (int i = node.level + 1; i < n; ++i)
    {
        int minCost = INT_MAX;
        for (int j = 0; j < n; ++j)
        {
            if (!node.assigned[j] && costMatrix[i][j] < minCost)
            {
                minCost = costMatrix[i][j];
            }
        }
        lb += minCost;
        cout << minCost << " ";
    }
    cout << ", 总下界: " << lb << endl;
    return lb;
}
// 分支限界法求解任务分配问题
int solveAssignmentProblem(const vector<vector<int>> &costMatrix)
{
    int n = costMatrix.size();
    Node root = {-1, 0, vector<bool>(n, false)};
    pq.push(root);

    int minCost = INT_MAX;
    while (!pq.empty())
    {
        Node node = pq.top();
        pq.pop();

        // 输出当前节点信息
        cout << "遍历节点，层级: " << node.level << ", 成本: " << node.cost << ", 分配: ";
        for (int i = 0; i < n; ++i)
        {
            cout << (node.assigned[i] ? "是" : "否") << " ";
        }
        cout << endl;

        if (node.level == n - 1)
        {
            minCost = min(minCost, node.cost);
            continue;
        }

        // 扩展当前节点
        for (int j = 0; j < n; ++j)
        {
            if (!node.assigned[j])
            {
                Node child = node;
                child.level++;
                child.assigned[j] = true;
                child.cost += costMatrix[child.level][j];

                int lb = lowerBound(child, costMatrix);
                if (lb < minCost)
                {
                    pq.push(child);
                    cout << "扩展节点，成本: " << child.cost << ", 下界: " << lb << endl;
                }
            }
        }
    }
    return minCost;
}

int main()
{
    vector<vector<int>> costMatrix = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}};

    int result = solveAssignmentProblem(costMatrix);
    cout << "最小总成本: " << result << endl;
    return 0;
}