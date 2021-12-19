//题解太多，以后写在这里面，还可以按顺序进行排列 本周除了这个文件夹的题目还有26 45 46 47 66题
//以后有时间会逐步把以前的题目挪进来
//21.合并两个有序数组
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *head=new ListNode(0);
        ListNode *current=head;
        ListNode *currentlist1=list1;
        ListNode *currentlist2=list2;
        while(currentlist1!=nullptr&&currentlist2!=nullptr){
            if(currentlist1->val>currentlist2->val){ 
            current->next=currentlist2;
            currentlist2=currentlist2->next;
            current=current->next;
            }
            else{   
                current->next=currentlist1;
                currentlist1=currentlist1->next;
                current=current->next;
            }
        }
        if(currentlist1==nullptr)current->next=currentlist2;
        else current->next=currentlist1;
        return head->next;
    }
};
//69.Sqrt(x)
class Solution {
public:
    int mySqrt(int x) {
    if(x==1)return 1;
    int left=0,right=x;
    int mid;
    while(right-left>1) {
         mid=(left+right)/2;
          if(x/mid<mid)right=mid;
          else left=mid;
    }
    return left;
 }
};
//86.分割链表
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
    ListNode* partition(ListNode* head, int x) {
       ListNode *small=new ListNode(0);
       ListNode *large=new ListNode(0);
       ListNode *smallhead,*largehead;
       smallhead=small;
       largehead=large;
       while(head!=nullptr){
           if(head->val>=x){
               large->next=head;
               large=large->next;
           }
           else{
               small->next=head;
               small=small->next;
           }
           head=head->next;
       }
        large->next=nullptr;
       small->next=largehead->next;
       return smallhead->next;
       }
};
