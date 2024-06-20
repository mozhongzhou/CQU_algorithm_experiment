#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

struct Job
{
    int id;
    int m1Time;
    int m2Time;
};

struct State
{
    vector<int> jobSequence; // 存储作业ID
    int totalTime;           // 当前完成时间
    int lowerBound;          // 当前状态的下界

    bool operator<(const State &other) const
    {
        return lowerBound > other.lowerBound;
    }
};

// 更新calculateTotalTime函数以考虑M1和M2阶段
int calculateTotalTime(const vector<int> &jobSequence, const vector<Job> &jobs)
{
    int m1Time = 0, m2Time = 0;
    for (int id : jobSequence)
    {
        const Job &job = jobs[id - 1];             // 假设作业ID从1开始
        m1Time += job.m1Time;                      // M1阶段累加
        m2Time = max(m2Time, m1Time) + job.m2Time; // M2阶段在M1完成后开始
    }
    return m2Time; // 返回总完成时间
}

// 计算当前状态的下界
int calculateLowerBound(const vector<int> &jobSequence, const vector<Job> &jobs)
{
    vector<int> remainingJobs;
    for (const Job &job : jobs)
    {
        if (find(jobSequence.begin(), jobSequence.end(), job.id) == jobSequence.end())
        {
            remainingJobs.push_back(job.id);
        }
    }

    // 初始下界是当前完成时间
    int lowerBound = calculateTotalTime(jobSequence, jobs);

    // 累加所有未调度作业的最短处理时间（启发式下界）
    for (int id : remainingJobs)
    {
        const Job &job = jobs[id - 1];
        lowerBound += min(job.m1Time, job.m2Time);
    }

    // 调试信息
    cout << "当前序列: ";
    for (int id : jobSequence)
    {
        cout << id << " ";
    }
    cout << " | 初始下界: " << calculateTotalTime(jobSequence, jobs) << " | 增加的时间: ";
    for (int id : remainingJobs)
    {
        cout << min(jobs[id - 1].m1Time, jobs[id - 1].m2Time) << " ";
    }
    cout << " | 总下界: " << lowerBound << endl;

    return lowerBound;
}

int main()
{
    vector<Job> jobs = {
        {1, 5, 6},  // 作业1
        {2, 12, 2}, // 作业2
        {3, 4, 14}, // 作业3
        {4, 8, 7}   // 作业4
    };
    priority_queue<State> states;
    states.push({{}, 0, 0});

    int bestTime = numeric_limits<int>::max();

    while (!states.empty())
    {
        State current = states.top();
        states.pop();

        if (current.jobSequence.size() == jobs.size())
        {
            bestTime = min(bestTime, current.totalTime);
            cout << "找到解，总时间: " << current.totalTime << endl;
            break;
        }

        for (const Job &job : jobs)
        {
            if (find(current.jobSequence.begin(), current.jobSequence.end(), job.id) == current.jobSequence.end())
            {
                vector<int> newSequence = current.jobSequence;
                newSequence.push_back(job.id);
                int newTotalTime = calculateTotalTime(newSequence, jobs);
                int newLowerBound = calculateLowerBound(newSequence, jobs);

                if (newLowerBound < bestTime)
                {
                    cout << "当前节点的下界: " << newLowerBound << endl;
                    states.push({newSequence, newTotalTime, newLowerBound});
                }
            }
        }
    }

    cout << "最佳总时间: " << bestTime << endl;

    return 0;
}
