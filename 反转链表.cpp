/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) // 0->1->2->3->4
    {
        ListNode *pre = NULL, *cur = head, *succ;
        while (cur) {
            succ = cur->next;
            cur->next = pre;
            pre = cur, cur = succ;
        }
        return pre;
    }
};