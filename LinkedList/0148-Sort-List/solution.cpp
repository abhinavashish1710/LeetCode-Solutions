class Solution {
    ListNode* merge(ListNode* a,ListNode* b) {
        ListNode d(0),*p=&d;
        while(a&&b){
            if(a->val<b->val) p->next=a,a=a->next;
            else p->next=b,b=b->next;
            p=p->next;
        }
        p->next=a?a:b;
        return d.next;
    }

public:
    ListNode* sortList(ListNode* head) {
        if(!head||!head->next) return head;

        ListNode *slow=head,*fast=head->next;
        while(fast&&fast->next)
            slow=slow->next,fast=fast->next->next;

        ListNode* mid=slow->next;
        slow->next=nullptr;

        return merge(sortList(head),sortList(mid));
    }
};
