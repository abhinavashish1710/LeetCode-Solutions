class Solution {
public:
    void reorderList(ListNode* head) {
        if(!head || !head->next) return;

        // Find middle
        ListNode *slow=head,*fast=head;
        while(fast->next&&fast->next->next){
            slow=slow->next;
            fast=fast->next->next;
        }

        // Reverse second half
        ListNode *cur=slow->next,*prev=nullptr;
        slow->next=nullptr;
        while(cur){
            ListNode *next=cur->next;
            cur->next=prev;
            prev=cur;
            cur=next;
        }

        // Merge two halves
        ListNode *a=head,*b=prev;
        while(b){
            ListNode *x=a->next,*y=b->next;
            a->next=b;
            b->next=x;
            a=x;
            b=y;
        }
    }
};
