#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

/*
给你一个长度为 2 * n 的整数数组。你需要将 nums 分成 两个 长度为 n 的数组，分别求出两个数组的和，
并最小化两个数组和之差的绝对值 。nums 中每个元素都需要放入两个数组之一。
请你返回最小的数组和之差。
*/

/*因为要求分后的数组是个数一样的，所以折半搜索,减少运算量
A和B是对称的，只要算一半就可以。区分A和B的关键是A永远包含第一个数,但这样做的前提是对nums要排序，
对于少一半的计算量，排30个数的序，划算！从前N个数中选i个，则应当从后N个数中选n−i个。这时就变成了一个经典问题：
从两个数组中各选择一个数，使得它们的和最接近某一个给定的数，对两个数组分别排序后使用双指针求解。
排序和去重。使用数组代替容器。
*/
class Solution
{
private:
    static constexpr int N = 6435;
    // arr[0][0~N]统计每种情况的和 比如arr[0][1]是在1~n中选择一个数的结果，但是选择1个数也有很多种情况
    int arr[2][N];
    int idx[2];
    int n = 0;

public:
    void dfs(const vector<int> &nums, const int l, const int r, int cur, int cnt)
    {
        //好像只对进入递归时，cnt就为0才会生效，还是有必要的，开头不加，后面cnt--了，就会多迭代很多次
        if (cnt == 0)
        {
            int i = (r == n) ? 0 : 1;
            idx[i] = 1;
            arr[i][0] = 0;
            return;
        }
        if (r - l < cnt)
            return;

        /* not choose l */
        dfs(nums, l + 1, r, cur, cnt);

        /* choose l */
        cur += nums[l];
        --cnt;
        if (cnt == 0)
        {
            int i = (r == n) ? 0 : 1; // 区分是哪个子数组
            arr[i][idx[i]] = cur;
            ++idx[i];
            return;
        }
        dfs(nums, l + 1, r, cur, cnt);
    }
    int minimumDifference(vector<int> &nums)
    {
        int sm = accumulate(nums.begin(), nums.end(), 0);
        int ans = INT_MAX;

        n = nums.size() / 2;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; ++i)
        {
            // 每次开始都会重新赋初值
            idx[0] = idx[1] = 0;
            //从A中选取i个数,A是从0到n-1，因为0默认包含，从1到n-1,共n-1个数
            dfs(nums, 1, n, 0, i); // A一定包含nums[0]?为什么
            //从B中选取n-i个数,n到2*n-1,共n个数
            dfs(nums, n, 2 * n, 0, n - i - 1); // B为什么从n开始，实际选不到2*n,终点索引是2*n-1
            sort(arr[0], arr[0] + idx[0]);
            // unique对元素去重，返回值是不重复的数组的尾地址，
            // idx是不重复的方案数.
            idx[0] = unique(arr[0], arr[0] + idx[0]) - arr[0]; // 计算偏移量，这是按照类型来的，不是按照字节
            sort(arr[1], arr[1] + idx[1]);
            idx[1] = unique(arr[1], arr[1] + idx[1]) - arr[1];

            //为什么b=idx[x]-1;这个-1是为什么？-1是因为A组默认从包含一个数开始
            // idx[1]应该是b组不重复的和
            int a = 0, b = idx[1] - 1, t;
            while (a < idx[0] && b >= 0)
            {
                // 注意nums【0】默认在A中，所以dfs计算时没有计算
                t = 2 * (nums[0] + arr[0][a] + arr[1][b]) - sm;
                ans = min(ans, abs(t));
                // ans=0或者sum是奇数，并且差为1
                if (ans == 0 || ((sm & 1) && ans == 1))
                    return ans;

                if (t > 0) // 在B组的选取多了
                    --b;
                else
                    ++a;
            }
        }

        return ans;
    }
};