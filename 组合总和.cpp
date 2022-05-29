//给你一个无重复元素的整数数组candidates和一个目标整数target，
//找出candidates中可以使数字和为目标数target的所有不同组合 ，并以列表形式返回。
//你可以按 任意顺序 返回这些组合。
// candidates中的同一个数字可以无限制重复被选取。如果至少一个数字的被选数量不同，则两种组合是不同的。 
//对于给定的输入，保证和为 target 的不同组合数少于 150 个。
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*1:广度优先搜索
结果有点问题，容易出现重复数组
怎么剔除重复数组呢？
记录下当前位置，如果临时数组是遍历到后面的位置了，则临时数组将不能再使用之前的元素，这样可以避免元素重复
*/
class Solution
{
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> vv;
        queue<vector<int>> q;
        queue<pair<int,int>> Sum;//存和和起点id
        for (size_t i = 0; i < candidates.size(); ++i)
        {
            if (candidates[i] < target)
            {
                q.push({candidates[i]});
                Sum.push({candidates[i],i});
            }
            else if(candidates[i]==target)
            {
                vv.push_back({candidates[i]});
            }
        }
        while (!q.empty())
        {
            int size = q.size();
            for (size_t i = 0; i < size; ++i)
            {
                auto x = q.front();
                auto [s,begin] = Sum.front();
                q.pop();
                Sum.pop();
                for (size_t j = begin; j < candidates.size(); ++j)
                {
                    int dis = target - s;
                    if (dis == candidates[j])
                    {
                        if (vv.size() == 150)
                            break;
                        x.push_back(candidates[j]);
                        vv.push_back(x);
                        x.pop_back();
                    }
                    else if (candidates[j] < dis)
                    {
                        x.push_back(candidates[j]);
                        q.push(x);
                        Sum.push({s + candidates[j],j});
                        x.pop_back();
                    }
                }
            }
        }
        return vv;
    }
};
/*递归
递归为什么没有重复数组呢？
因为递归使用的是从当前idx开始的遍历累加，如[2,3,6,7]
即可以出现2，2，3，但是3不会出现2，因为有前提条件，数组中每个元素互不相同
前面的数，一旦使用了后面的数，则不能使用前面的数*/
class Solution1
{
public:
    void dfs(vector<int> &candidates, int target, vector<vector<int>> &ans, vector<int> &combine, int idx)
    {
        if (idx == candidates.size())
        {
            return;
        }
        if (target == 0)
        {
            ans.emplace_back(combine);
            return;
        }
        // 直接跳过
        dfs(candidates, target, ans, combine, idx + 1); //选择不用，跳过第idx个数，
        // 选择当前数
        if (target - candidates[idx] >= 0)
        {
            combine.emplace_back(candidates[idx]);
            dfs(candidates, target - candidates[idx], ans, combine, idx);
            combine.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> ans;
        vector<int> combine;
        dfs(candidates, target, ans, combine, 0);
        return ans;
    }
};
int main()
{
    vector<int> candidates{4,7,5,6};
    int target = 16;
    Solution plan;
    auto x = plan.combinationSum(candidates, target);
    for (size_t i = 0; i < x.size(); ++i)
    {
        for ( auto j:x[i])
        {
            cout<<" j  = "<<j<<endl; 
        }
        cout<<endl;
    }
    
    return 0;
}

// c++11的新标准，使用shrink_to_fit退回容器不需要的内存空间