// 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
// k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
// 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *_next) : val(x), next(_next) {}
};

class Solution
{
public:
    //这里的反排序已经将tail->next按照反序连接了，大排序中就不要考虑这了
    pair<ListNode *, ListNode *> myReverse(ListNode *head, ListNode *tail)
    {
        ListNode *begin = head;
        ListNode *pre = tail->next;
        while (pre != tail)
        {
            ListNode *nex = head->next;
            head->next = pre;
            pre = head;
            head = nex;
        }
        return {tail, begin};
    }
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        //先创建一个哑节点，避免反序后找不到头结点
        ListNode *yummy = new ListNode();
        yummy->next = head;
        ListNode *pre = yummy;
        while (head)
        {
            ListNode *tail = pre;
            // 查看剩余部分长度是否大于等于 k
            // 举例k=2，从哑结点移动2次才是子段；如果从head开始移动，则会多移动一个
            for (int i = 0; i < k; i++)
            {
                tail = tail->next;
                if (!tail)
                    return yummy->next;
            }
            pair<ListNode *, ListNode *> result = myReverse(head, tail);
            head = result.first;
            tail = result.second;
            //将反序后的链表接入原链表
            pre->next = head;
            //更新pre和head
            pre = tail;
            head = tail->next;
        }
        return yummy->next;
    }
};