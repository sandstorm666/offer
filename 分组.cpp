#include <vector>
#include <iostream>
using namespace std;

int cnt = 0;

/*j可看成是B中元素，因为要求B中元素要大于A中对应位置的元素，j在有序数组中总是比i大，从而满足了这个条件；
注意每次递归，idx+1，idx是统计元素个数
cnt是统计符合要求的元素个数。*/
void getRes(const vector<int> &nums, vector<int> &visited, int idx)
{
    if (idx == nums.size() / 2)
        ++cnt;
    for (int i = 0; i < nums.size(); ++i)
    {
        if (!visited[i])
        {
            visited[i] = true;
            for (int j = i + 1; j < nums.size(); ++j)
            {
                if (!visited[j])
                {
                    visited[j] = true;
                    getRes(nums, visited, idx + 1);
                    visited[j] = false;
                }
            }
            visited[i] = false;
        }
    }
}

int main()
{
    vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> visited(nums.size());
    getRes(nums, visited, 0);
    cout << cnt << endl;
    return 0;
}