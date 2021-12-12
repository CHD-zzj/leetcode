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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry=0;
        ListNode *head=new ListNode(0);
        ListNode *pre=head;
        while(l1||l2)
        {
            int sum=0;
            if(l1!=nullptr)
            {
                sum+=l1->val;
                l1=l1->next;
            }
            if(l2!=nullptr)
            {
                sum+=l2->val;
                l2=l2->next;
            }
            sum+=carry;
            if(sum>=10)
            {
                sum=sum%10;
                carry=1;
            }
            else{
                carry=0;
            }
            ListNode *current=new ListNode(sum);
            pre->next=current;
            pre=pre->next;
        }  
        if(carry)
        {
            pre->next=new ListNode(1);
        }
        return head->next;
    }
};
