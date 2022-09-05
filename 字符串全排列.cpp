#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

void backTrack(vector<string> &ans, string nums, int first, int len)
{
    if (first == len)
    {
        ans.emplace_back(nums);
        return;
    }
    for (size_t i = first; i < len; ++i)
    {
        swap(nums[i], nums[first]);
        backTrack(ans, nums, first + 1, len);
        swap(nums[first], nums[i]);
    }
}
int main()
{
    string s;
    cin >> s;
    // s = "abcdefghi";
    vector<string> collections;
    string str = "abcdefghi";
    backTrack(collections, str, 0, (int)str.size());
    sort(collections.begin(), collections.end());
    // cout << "collection = " << collections.size() << endl;
    auto it = find(collections.begin(), collections.end(), s);
    if (it == collections.begin())
    {
        cout << "null\n";
        cout << *(++it) << endl;
    }
    else if (it == collections.begin())
    {
        cout << *(--it) << endl;
        cout << "null\n";
    }
    else
    {
        cout << *(--it) << endl;
        cout << *(++it) << endl;
    }
}