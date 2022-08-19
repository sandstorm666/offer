// m*n的迷宫，有k个宝箱；
// 先收集距离他曼哈顿距离最小的宝箱，如果有多个就选定编号最小的。
// 曼哈顿距离为行差+列差
// 输入第一行为一个正整数T，表示有T组数据。
// 每组数据的第一行为两个正整数m和n，分别表示迷宫地图的行数和列数。
// 接下来有m行，每行有n个字符，表示迷宫地图中这行每一个中的图例表示。图例如下：
// #: 障碍格；
// *: 冒险者当前位置，为通行格；
// 0-9: 每个宝箱所在位置，为通行格；
// .: 其它通行格
// 其中冒险者当前位置在一个迷宫地图中是有且仅有一个的。表示宝箱的数字，在一个迷宫地图中最多只会出现一次，
// 且如果有一个k（k>0)号宝箱在迷宫地图中，则k-1号宝箱也必定会在迷宫地图中。
// 数据范围：对于所有数据，满足1<=T<=5, 1<=m<=50, 1<=n<=50。
// #include <__msvc_all_public_headers.hpp> 万能头文件
#include <string.h>
#include <iostream>
#include <queue>
using namespace std;
// 先计算每个宝箱到所有点的最短距离，然后从起点开始搜索
// 每次搜索前先遍历所有宝箱的位置，选定一个符合要求的宝箱后开始搜索，如果搜索完所有宝箱，返回步数，否则返回-1
struct node
{
    int x, y, t;
} A[10]; //起别名，同时定义数组

char mp[55][55];
bool book[55][55];  //访问过的节点
int dp[55][55][10]; //记录宝箱到每个点的最短距离
int m, n;
//方向
int tx[4] = {0, 1, 0, -1};
int ty[4] = {1, 0, -1, 0};
int cnt;
void bfs(int x, int y, int id) //计算宝箱到每个点的最短距离（第一次到达就是最短。）
{
    memset(book, 0, sizeof(book));
    int cnt = 0;
    queue<node> q;
    node a;
    a.x = x;
    a.y = y;
    a.t = 0; // 代表步数
    book[x][y] = true;
    q.push(a);
    while (!q.empty())
    {
        node w = q.front();
        q.pop();
        //不用统计上一层的size?
        for (int i = 0; i < 4; i++)
        {
            int xx = w.x + tx[i];
            int yy = w.y + ty[i];
            int temp = w.t + 1;
            if (xx >= 1 && xx <= m && yy >= 1 && yy <= n && !book[xx][yy] && mp[xx][yy] != '#')
            {
                book[xx][yy] = true;
                dp[xx][yy][id] = temp;
                q.push(node{xx, yy, temp});
            }
        }
    }
}

int Bfs(int x, int y, int t) // 从起点开始搜寻宝箱
{
    node a;
    a.x = x;
    a.y = y;
    a.t = t;
    memset(book, 0, sizeof(book));
    book[x][y] = 1;
    queue<node> q;
    q.push(a);
    int p = 0;
    while (!q.empty())
    {
        node w = q.front();
        q.pop();
        // A.t什么时候不为0?找到曾经找过的宝箱时，不为0
        if (mp[w.x][w.y] >= '0' && mp[w.x][w.y] <= '9' && A[mp[w.x][w.y] - '0'].t == 0)
        {
            memset(book, 0, sizeof(book));
            book[w.x][w.y] = 1;
            A[mp[w.x][w.y] - '0'].t = 1;
            p++;
        }
        if (p == cnt) // p等于宝箱个数，跳出
        {
            return w.t;
        }
        int maxn = 100005;
        int id;
        // 计算当前点到10个宝箱的曼哈顿距离。这步有什么用？因为每走一步都要判断
        for (int i = 0; i < cnt; i++)
        {
            if (abs(A[i].x - w.x) + abs(A[i].y - w.y) < maxn && A[i].t == 0) // <保证了，如果有多个距离相等的，取编号最小的
            {
                maxn = abs(A[i].x - w.x) + abs(A[i].y - w.y);
                id = i;
            }
        }
        // 如果出现反复横跳，当前的路径放弃，不入队列了
        for (int i = 0; i < 4; i++)
        {
            int xx = w.x + tx[i];
            int yy = w.y + ty[i];
            int temp = w.t + 1; // 搜寻距离
            // dp[xx][yy][id] < dp[w.x][w.y][id]避免反复横跳，走一步，前往宝箱的曼哈顿距离-1才更新
            if (xx >= 1 && xx <= m && yy >= 1 && yy <= n && !book[xx][yy] && mp[xx][yy] != '#' && dp[xx][yy][id] < dp[w.x][w.y][id])
            {
                book[xx][yy] = 1;
                q.push(node{xx, yy, temp});
            }
        }
    }
    return -1;
}
int main()
{
    int t, x, y;
    cin >> t;
    while (t--)
    {
        memset(dp, 0, sizeof(dp));
        cin >> m >> n;
        cnt = 0;
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cin >> mp[i][j];
                if (mp[i][j] == '*') //当前位置
                {
                    x = i;
                    y = j;
                }
                else if (mp[i][j] >= '0' && mp[i][j] <= '9') //宝箱
                {
                    A[mp[i][j] - '0'].x = i;
                    A[mp[i][j] - '0'].y = j;
                    cnt++;
                }
            }
        }
        for (int i = 0; i < cnt; i++)
        {
            bfs(A[i].x, A[i].y, i);
        }
        int ans = Bfs(x, y, 0);
        cout << ans << "\n";
        for (int i = 0; i < cnt; i++)
        {
            A[i].t = 0;
            A[i].x = 0;
            A[i].y = 0;
        }
    }
}
