// 有一堆石头，用整数数组stones表示。其中stones[i]表示第i块石头的重量。
// 每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为x和y，且x<=y。那么粉碎的可能结果如下：
// 如果 x == y，那么两块石头都会被完全粉碎；
// 如果 x != y，那么重量为x的石头将会完全粉碎，而重量为y的石头新重量为y-x。
// 最后，最多只会剩下一块石头。返回此石头最小的可能重量 。如果没有石头剩下，就返回0。
#include <vector>
#include <iostream>
#include <numeric>
using namespace std;

/*转化为0-1背包问题
将石头分为2组，让两组的差最小。
定义二维布尔数组dp，其中dp[i+1][j]表示前i个石头能否凑出重量j。特别，dp[0][]为不选任何石头的状态，因此除了dp[0][0]为真，其余dp[0][j]为假；
对于第 i 个石头，考虑凑出重量 j：
若 j<stones[i]，则不能选第 i个石头，此时有 dp[i+1][j]=dp[i][j];维持上一层j重量的状态
若 j≥stones[i]，存在选或不选两种决策，不选时有 dp[i+1][j]=dp[i][j]，选时需要考虑能否凑出重量j−stones[i]，即 dp[i+1][j]=dp[i][j−stones[i]]。
若二者均为假则 dp[i+1][j] 为假，否则 dp[i+1][j] 为真。
*/
class Solution
{
public:
    int lastStoneWeightII(vector<int> &stones)
    {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int n = stones.size();
        int target = sum / 2; //如果是奇数，target比中点少1；但是对结果没影响。
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1; //初值是true
        // dp 下标最大时n,target
        for (int i = 0; i < n; ++i) //第i个石头
        {
            for (int j = 0; j < target + 1; ++j) // 石头值是否存在
            {
                if (j < stones[i]) // 维持j重量状态，如果能凑出j,那么同一列的j都会逐渐更新为1
                {
                    dp[i + 1][j] = dp[i][j];
                }
                else if (j >= stones[i]) // j-stones[i]为真
                {
                    dp[i + 1][j] = dp[i][j - stones[i]] || dp[i][j];
                }
            }
        }
        // 从高度往下递归，找最接近的符合条件的数
        int ans = 0;
        for (int j = target; j >= 0; j--)
        {
            if (dp[n][j])
            {
                ans = j;
                break;
            }
        }
        return abs(sum - 2 * ans);
    }
};
class Solution
{
public:
    int lastStoneWeightII(vector<int> &stones)
    {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int n = stones.size(), m = sum / 2;
        // +1是为了方便计数，从1开始计算
        vector<vector<int>> dp(n + 1, vector<int>(m + 1)); // 用int表示bool类型
        dp[0][0] = true;                                   //赋初值
        // 循环首先会将每个石块值赋初值
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j <= m; ++j)
            {
                if (j < stones[i])
                {
                    dp[i + 1][j] = dp[i][j];
                }
                else
                {
                    dp[i + 1][j] = dp[i][j] || dp[i][j - stones[i]];
                }
            }
        }
        // 从高到低遍历，j就代表最接近sum/2的子数组和
        for (int j = m;; --j)
        {
            if (dp[n][j])
            {
                return sum - 2 * j;
            }
        }
    }
};