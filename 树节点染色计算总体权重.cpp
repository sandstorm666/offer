// 给你一棵树，树上每个节点要么是红色要么是黑色，根节点为1。
// 每个节点的权重值为根节点到该节点路径上红色节点个数和蓝色节点个数的差的绝对值。求所有节点权重值之和。
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
vector<int> mp[N];        // mp是个二维数组，N代表第一维长度,表示N个vector
int cred[N], cblue[N], n; // cred:统计到当前节点时红色节点个数，索引代表节点；cblue同理；n代表节点个数
string color;
ll ans;
/*深度优先搜索
每次dfs计算两个节点的颜色差。
当v=fa 不进入递归函数，从而跳过递归重复路径陷入死循环。
*/
void dfs(int u, int fa)
{
    cred[u] = cred[fa];
    cblue[u] = cblue[fa];
    if (color[u] == 'R')
    {
        cred[u]++;
    }
    else
    {
        cblue[u]++;
    }
    // cout<<u<<" "<<cred[u]<<" "<<cblue[u]<<endl;
    ans += abs(cred[u] - cblue[u]);
    for (auto v : mp[u])
    {
        if (v == fa) //代表路径已经走过
            continue;
        dfs(v, u);
    }
    return;
}
/*
5
RBBRB
1 5
2 5
1 3
5 4
*/
int main()
{
    cin >> n >> color;
    color = " " + color; // 前面加个空格，因为dfs时u从1开始
    for (int i = 0, u, v; i < n - 1; i++)
    {
        cin >> u >> v;
        mp[u].push_back(v);
        mp[v].push_back(u);
    }
    dfs(1, 0);
    cout << ans << endl;
}