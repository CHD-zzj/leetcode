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
    int getlen(ListNode *head){
        int len=0;
        while(head!=nullptr)
        {
            ++len;
            head=head->next;
        }
        return len;
    }
    ListNode* removeNthFromEnd(ListNode* head, int n) {
       int lenth=getlen(head);
       ListNode *p=new ListNode(0,head);
       ListNode* cur=p;
       for(int i=1;i<lenth-n+1;++i)
       {
           cur=cur->next;
       }
       cur->next=cur->next->next;
       ListNode *ans=p->next;
       delete p;
       return ans;
       }
};
