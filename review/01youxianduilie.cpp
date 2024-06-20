#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node
{
    int level;   // 物品编号
    int profit;  // 当前价值
    int weight;  // 当前重量
    float bound; // 上界
};

// 计算上界
float bound(Node u, int n, int W, vector<int> &wt, vector<int> &val)
{
    if (u.weight >= W)
        return 0;
    float result = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;
    while ((j < n) && (totweight + wt[j] <= W))
    {
        totweight += wt[j];
        result += val[j];
        j++;
    }
    if (j < n)
        result += (W - totweight) * val[j] / wt[j];
    return result;
}

// 比较函数，用于优先队列
struct Compare
{
    bool operator()(Node &a, Node &b)
    {
        return a.bound < b.bound;
    }
};

// 0/1背包问题的分支限界法求解
int knapsack(int W, vector<int> &wt, vector<int> &val, int n)
{
    priority_queue<Node, vector<Node>, Compare> Q;
    Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    u.bound = bound(u, n, W, wt, val);
    Q.push(u);
    int maxProfit = 0;
    while (!Q.empty())
    {
        u = Q.top();
        Q.pop();
        // 在Q.pop()之后输出
        cout << "出队节点: Level=" << u.level << ", Profit=" << u.profit << ", Weight=" << u.weight << ", Bound=" << u.bound << endl;

        if (u.bound > maxProfit)
        {
            v.level = u.level + 1;
            v.weight = u.weight + wt[v.level];
            v.profit = u.profit + val[v.level];
            // 在检查v.weight和v.profit之后输出
            cout << "创建节点: Level=" << v.level << ", Profit=" << v.profit << ", Weight=" << v.weight << ", Bound=" << bound(v, n, W, wt, val) << " (包含物品)" << endl;
            if (v.weight <= W && v.profit > maxProfit)
            {
                maxProfit = v.profit;
            }
            v.bound = bound(v, n, W, wt, val);
            if (v.bound > maxProfit)
            {
                Q.push(v);
            }
            v.weight = u.weight;
            v.profit = u.profit;
            v.bound = bound(v, n, W, wt, val);
            // 在重新计算v.bound之后输出
            cout << "创建节点: Level=" << v.level << ", Profit=" << v.profit << ", Weight=" << v.weight << ", Bound=" << v.bound << " (不包含物品)" << endl;
            if (v.bound > maxProfit)
            {
                Q.push(v);
            }
        }
        cout << "访问节点: Level=" << u.level << ", Profit=" << u.profit << ", Weight=" << u.weight << ", Bound=" << u.bound << endl;
    }
    return maxProfit;
}

int main()
{
    int W = 30;                     // 背包容量
    vector<int> val = {45, 25, 25}; // 物品价值
    vector<int> wt = {16, 15, 15};  // 物品重量
    int n = val.size();
    cout << "最大价值为: " << knapsack(W, wt, val, n) << endl;
    return 0;
}