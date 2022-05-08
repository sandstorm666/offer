//输入一个链表，输出该链表中倒数第k个节点。
//为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。
#include<iostream>
#include<stack>
using namespace std;
class ListNode {
public:
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(nullptr){}
};
/*借助栈的特性*/
//class Solution {
//public:
//	ListNode* getKthFromEnd(ListNode* head, int k) {
//		ListNode* pre=head;
//		stack<ListNode*> s;
//		while (pre)//节点存在
//		{
//			s.push(pre);
//			pre = pre->next;
//		}
//		while (k>0)
//		{
//			pre = s.top();
//			s.pop();
//			k--;
//		}
//		return pre;
//	}
//};
/*递归+回溯思想将链表反转
回溯是在递归函数的调用后进行的操作。
和题意不符合，题目要求返回的链表还是正序输出的*/
class Solution {
public:
	ListNode* getKthFromEnd(ListNode* head, int k) {
		auto n = inverse(head);
		ListNode* node=n;
		while (k>0)
		{
			n = n->next;
			k--;
			node = n;
		}
		return node;
	}
	ListNode* inverse(ListNode* head)
	{
		if (!head||!head->next)//
			return head;
		ListNode* n=inverse(head->next);//递归，一直到倒数第1个节点结束,结束时n为最后一个节点
		head->next->next = head; //head为倒数第2个节点
		head->next = nullptr;
		return n;
	}
};
int main()
{
	ListNode a0(0), a1(1), a2(2);
	a0.next = &a1;
	a1.next = &a2;
	Solution plan;
	auto n = plan.inverse(&a0);
	cout << "val = " << n->val << endl;
	return 0;
}