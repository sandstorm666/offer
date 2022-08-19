/*推荐股票
完成股票推荐系统设计，每个用户可能关注几个公司，比如A,B,C，如果有另一个用户只关注了A，那么就会给他推荐B，C。
这时候如果来了一个用户关注C，D，那么后来关注C的用户，都会推荐A，B，关注A的用户都会推荐BCD。
在有上面的关系后，求用户查询的时候，会给它推荐的公司的个数。*/
#include <iostream>
#include <vector>
#include <map>
using namespace std;
/*map
将公司和人全部先用map存储起来，
然后两个数组，一个记录父节点下标，一个记录相同拥有相同的父节点的节点个数
在输入的同时完成记录*/
typedef long long ll;
const int N = 1e5 + 5;
int tot;
map<string, int> name;  // 公司name
map<string, int> pname; // 人name
map<int, int> mp;       // 存放当前查询时，该人关注的公司数量
int fa[N], sz[N];       // fa记录父节点，sz记录拥有相同的父节点的节点个数
//寻找父节点下标
int getfa(int u)
{
    return fa[u] != u ? fa[u] = getfa(fa[u]) : u;
    // return fa[u] != u ? getfa(fa[u]) : u;也可以
}
//合并节点：同一父节点
void join(int u, int v)
{
    int f1 = getfa(u), f2 = getfa(v);
    if (f1 != f2)
    {
        fa[f2] = fa[f1];
        sz[f1] += sz[f2];
        // cout << "sz [" << f1 << "] = " << sz[f1] << endl;
        sz[f2] = 0;
    }
}

/*
5
1 Alice 2
Zoom Apple
2 Bob
2 Alice
1 Bob 2
Apple Microsoft
2 Bob
*/
int main()
{
#pragma region
    //以下这段代码可以取消iostream的输入输出缓存，使的效率与scanf、printf相差无几。
    ios::sync_with_stdio(false);
    cin.tie(0); //解除cin与cout的绑定，因为每次执行<<，都会调用flush，增加io负担
    cout.tie(0);

    int q;
    cin >> q;
    int type, m;
    string in, bu; // in:人名，bu：公司名
    tot = q;       // 为什么tot要从q之后开始呢？因为前面q个作为潜在的父节点，thisroot会占用
#pragma endregion
    for (int i = 1; i <= q; i++)
    {
        cin >> type;
        if (type == 1) //插入
        {
            cin >> in >> m;
            int thisroot = i; // thisroot作为人名在索引中的根基
            // 除了加入到人的map中还做了什么？指定了当前节点的父节点为自己
            pname[in] = thisroot;
            fa[thisroot] = thisroot;
            sz[thisroot] = 0;

            for (int i = 0; i < m; i++)
            {
                cin >> bu;
                //加入公司的map中
                if (name.find(bu) == name.end())
                {
                    name[bu] = ++tot;
                    fa[name[bu]] = name[bu];
                    sz[name[bu]] = 1;
                }
                join(thisroot, name[bu]);
            }
            mp[thisroot] = m; //存放第thisroot客户当前关注的股票数
        }
        else // 查询
        {
            cin >> in;
            if (pname.find(in) == pname.end())
            {
                cout << "error\n";
                continue;
            }
            int pid = pname[in];        // pid即为thisroot
            int total = sz[getfa(pid)]; //注意这里getfa的调用
            int tonari = mp[pid];
            cout << total - tonari << "\n";
        }
    }
}
