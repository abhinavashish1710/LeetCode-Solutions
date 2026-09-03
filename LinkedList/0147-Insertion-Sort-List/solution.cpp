class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode dummy(0);

        while(head) {
            ListNode* cur=head;
            head=head->next;

            ListNode* p=&dummy;
            while(p->next && p->next->val<cur->val)
                p=p->next;

            cur->next=p->next;
            p->next=cur;
        }

        return dummy.next;
    }
};
