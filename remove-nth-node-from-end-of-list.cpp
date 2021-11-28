/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        auto sentry = new ListNode(-1, head);
        int size = 0;
        for (auto p = head; p; p = p->next)
            size++;
        auto q = sentry;
        for (int i = 0; i < size - n; ++i) {
            q = q->next;
        }
        q->next = q->next->next;
        return sentry->next;
    }
};