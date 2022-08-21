// 给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。
#include <vector>
using namespace std;
/*模拟
模拟还是得使用辅助数组记录访问过的节点。
当越界或者访问的下一个节点是访问过的，需要更换方向，下一个方向必是可以走的。
*/
/*分层
分层不需要辅助数组，分层需要记录每次可以走的行最小值和行最大值，列最小值和最大值。
从左到右遍历上侧元素，依次为（top,left)到(top,right)
从上到下遍历右侧元素，依次为(top+1,right)到(bottom,right-1)
从右到左遍历下侧元素，依次为(bottom,right)到(bottom,left+1)
从下到上遍历左侧元素，依次为(bottom,left)到(top+1,left)
遍历完后，left和top+1,right和bottom-1；进入下一层循环。
循环时计数，当循环的结点数=矩阵尺寸数时，结束。
*/
class Solution
{
public:
    pair<int, int> directions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<int> ans;
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        if (m == 0)
            return {};
        int n = matrix[0].size();
        if (n == 0)
            return {};
        vector<vector<int>> visited(m, vector<int>(n, 0)); //辅助矩阵
        int cnt = m * n;
        int x = 0, y = 0, dir = 0;
        for (int i = 0; i < cnt; ++i)
        {
            visited[x][y] = 1;
            ans.push_back(matrix[x][y]);
            int newX = x + directions[dir].first;
            int newY = y + directions[dir].second;
            //越界了或者访问到已访问的坐标，顺序更换方向
            if (newX >= m || newX < 0 || newY >= n || newY < 0 || visited[newX][newY])
            {
                dir = (dir + 1) % 4; //下一个方向必是通的
            }
            x += directions[dir].first;
            y += directions[dir].second;
        }
        return ans;
    }
};