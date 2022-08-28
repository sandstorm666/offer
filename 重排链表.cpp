struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
//找链表中点和普通的中点不一样，4个节点，应该移动1次到2号节点;
//如果是5个节点应该移动2次到3号节点,这样的中点应该是（n-1）/2;
//如果创建了哑结点还需要再考虑中点位置
//链表找中点位置的最好办法是快慢指针，可以直接返回中点位置。少一次for循环。
class Solution
{
public:
    //翻转链表，链表中最常见的操作
    ListNode *reverse(ListNode *head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode *tail = reverse(head->next);
        head->next->next = head;
        head->next = nullptr;
        return tail; //这里的tail等于尾节点，因为递归中止return head
    }
    void reorderList(ListNode *head)
    {
        if (!head || !head->next)
            return;
        //先统计节点个数吧
        int n = 0;
        ListNode *p = head;
        while (p)
        {
            ++n;
            p = p->next;
        }
        //找到中点
        int half = (n - 1) / 2;
        p = head;
        while (half--)
        {
            p = p->next;
        }
        // cout<<"p = "<<p->val<<endl;
        ListNode *tail = reverse(p);
        p = head;
        while (p)
        {
            ListNode *pn = p->next;
            ListNode *tn = tail->next;
            p->next = tail;
            tail->next = pn;
            p = pn;
            tail = tn;
        }
    }
};