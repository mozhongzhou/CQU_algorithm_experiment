#include <iostream>
#include <queue>
#include <vector>
// 检查当前位置是否可以放置皇后
bool isSafe(int board[4][4], int row, int col)
{
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
    for (int i = row, j = col; j >= 0 && i < 4; i++, j--)
        if (board[i][j])
            return false;
    return true;
}
// 使用队列的分支限界法求解4皇后问题
void solveNQ()
{
    int board[4][4] = {0};
    std::queue<std::pair<int, int>> Q;
    Q.push({0, 0});
    while (!Q.empty())
    {
        auto p = Q.front();
        Q.pop();
        int row = p.first, col = p.second;
        if (!isSafe(board, row, col))
            continue;
        board[row][col] = 1;
        if (col == 3)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                    std::cout << board[i][j] << " ";
                std::cout << std::endl;
            }
            return;
        }
        for (int i = 0; i < 4; i++)
            Q.push({i, col + 1});
        board[row][col] = 0;
    }
}
int main()
{
    solveNQ();
    return 0;
}
