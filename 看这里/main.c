//1.两数之和。
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};
//2.两数相加
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
//3.无重复字符的最长子串
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> char_set;
        int left=0,right=0,ans=0;
        for(;left<s.size();++left)
        {
            while(right<s.size()&&char_set.count(s[right])==0)
            {
                char_set.insert(s[right]);
                ans=max(ans,right-left+1);
                ++right;
            }
            char_set.erase(s[left]);
        }
        return ans;
    }
};
//4.寻找两个正序数组的中位数
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m,n;
        int i=0,j=0;
        double ans=0;
        m=nums1.size();
        n=nums2.size();
        nums1.push_back(9999999);
        nums2.push_back(9999999); 
        vector<int>num={};
        for(int k=0;k<m+n;k++)
        {
           
            if(nums1[i]<nums2[j]){
                num.push_back (nums1[i]);
                i++;
            }
            else{
                num.push_back(nums2[j]);
                j++;
            }
        }
        if((m+n)%2==0){
         ans = (double)(num[(m+n)/2] + num[(m+n)/2-1]) / 2;
         return ans;
        }
        else{
            ans= (double)num[(m+n)/2];
            return ans;
        } 
    }
};
//符合时间复杂度要求的做法
class Solution {
public:
//新做法，以前合并数组再找中位数的时间复杂度太大
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int m = nums1.size();
        int n = nums2.size();
        int left = 0, right = m;
        // median1：前一部分的最大值
        // median2：后一部分的最小值
        int median1 = 0, median2 = 0;
        while (left <= right) {
            // 前一部分包含 nums1[0 .. i-1] 和 nums2[0 .. j-1]
            // 后一部分包含 nums1[i .. m-1] 和 nums2[j .. n-1]
            int i = (left + right) / 2;
            int j = (m + n + 1) / 2 - i;
            // nums_im1, nums_i, nums_jm1, nums_j 分别表示 nums1[i-1], nums1[i], nums2[j-1], nums2[j]
            int nums_im1 = (i == 0 ? INT_MIN : nums1[i - 1]);
            int nums_i = (i == m ? INT_MAX : nums1[i]);
            int nums_jm1 = (j == 0 ? INT_MIN : nums2[j - 1]);
            int nums_j = (j == n ? INT_MAX : nums2[j]);
            if (nums_im1 <= nums_j) {
                median1 = max(nums_im1, nums_jm1);
                median2 = min(nums_i, nums_j);
                left = i + 1;
            } else {
                right = i - 1;
            }
        }
        return (m + n) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
    }
};
//6.字形变换
class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows==1)return s;
        vector<string>ans(min(numRows,int(s.size())));
        bool signal=false;
        int row=0;
        for(char c:s){
            ans[row]+=c;
            if(row==0||row==numRows-1){
                signal=!signal;
            }
           row+=signal ? 1:-1;
        }
    string ret;
    for(string rows:ans){
        ret +=rows;
        }
    return ret;
    }
};
//7.整数反转
class Solution {
public:
    //关键点在于如何判断溢出状况
    int reverse(int x) {
       if (x==0)return 0;
        int ans=0;
        while(x!=0){

            if(ans<INT_MIN/10||(ans==INT_MIN/10&&x<-8)){
     	//如果小于INT_MIN/10 还需要去添加下一位 则一定溢出
                //如果等于INT_MIN/10 且下一位还小于-8（8是INT_MIN最后一位）也会溢出
                //最大数判别溢出思想相同
                return 0;
            }
            if(ans>INT_MAX/10||(ans==INT_MAX/10&&x>7)){
                return 0;
            }
            ans=ans*10+x%10;
            x/=10;
        }
        return ans;
    
    }

};
//9.回文数
class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0||x%10==0&&x!=0)
        {return false;}
        else{
           int r=0;
           while(x>r){
               r=r*10+x%10;
               x/=10;
           }
           return x==r||x==r/10;
        }
    }//也能转换成字符串通过reverse反转，继而进行判断
};
//11.盛水最多的容器
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left=0;int right=height.size()-1;
        int ans=0; 
        if((right-left)<1) return -1;
        else{
        for(;left<right;){
            ans=max(ans,min(height[left],height[right])*(right-left));
            if(height[right]<height[left])--right;
            else ++left;
            }
        return ans;
        }
       
    }
};
//12.整数转罗马数字
class Solution {
public:
    string intToRoman(int num) {
    int values[]={1000,900,500,400,100,90,50,40,10,9,5,4,1};
    string reps[]={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    string ans;
    for(int i=0;i<13;i++){
        while(num>=values[i]){
            num-=values[i];
            ans+=reps[i];
        }
    }
    return ans;
    }
};
//13.罗马数字转整数
class Solution {
private:    
    unordered_map<char, int> symbolValues = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };
public:
int romanToInt(string s) {
    int ans=0;
    for(int i=0;i<s.length();++i)
    {
        int value=symbolValues[s[i]];
        if(i<s.length()-1&&value<symbolValues[s[i+1]])
        {
            ans-=value;
        }
        else{
            ans+=value;
        }
    }
    return ans;
}
   
};
//14.最长公共前缀
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int lenth=strs[0].size();
        int count=strs.size();
        for(int i=0;i<lenth;++i)
        {   char c=strs[0][i];
            for(int j=1;j<count;++j){
                if(i==strs[j].size()||c!=strs[j][i]){
                    return strs[0].substr(0,i);
                    //substr是截取字符串长度 返回的是内容 instr返回位置，两个参数 0为起始位置，i为截取长度
                }
            } 
        }
        return strs[0];

    }
};
//15.三数之和
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>>ans;
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size();++i){
          if(nums[i]>0)return ans;
          if(i>0&&nums[i]==nums[i-1])continue;  
          int L=i+1;int R=nums.size()-1;
           while(L<R){
               if(nums[i]+nums[L]+nums[R]>0){
                  R--;
               }
              else if(nums[i]+nums[L]+nums[R]<0){
                   L++;
               }
              else if(nums[i]+nums[L]+nums[R]==0){
              ans.emplace_back(vector<int>{nums[i],nums[L],nums[R]});
               while(R>L&&nums[R]==nums[R-1]){R--;}//去重操作
               while(R>L&&nums[L]==nums[L+1]){L++;}
               R--;
               L++;
               }
           }
        }
        return ans;
    }
};
//17.电话号码的字母组合
class Solution {
    private:
    const string letterMap[10] = {
        "", // 0
        "", // 1
        "abc", // 2
        "def", // 3
        "ghi", // 4
        "jkl", // 5
        "mno", // 6
        "pqrs", // 7
        "tuv", // 8
        "wxyz", // 9
    };
public:
    vector<string> result;//存放结果
    string s;//存放叶子节点的结果
    void backtracking(const string &digits,int index){
        if(index==digits.size()){
            result.push_back(s);
            return;
        }
        int digit=digits[index]-'0';
        string letters=letterMap[digit];
        for(int i=0;i<letters.size();++i){
            s.push_back(letters[i]);
            backtracking(digits,index+1);
            s.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        s.clear();
        result.clear();
        if(digits.size()==0){return result;}
        backtracking(digits,0);
        return result;
    }
};
//19.删除链表的倒数第N个结点
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
//20.有效的括号
class Solution {
public:
    bool isValid(string s) {
        int n=s.size();
        stack<int>Stack;
        for(int i=0;i<n;++i){
            if(s[i]=='(')
            {
                Stack.push(')');
            }
            else if(s[i]=='{')
            {
                Stack.push('}');
            }
           else if(s[i]=='['){
                Stack.push(']');
            }
            else if(Stack.empty()||Stack.top()!=s[i])return false;
            else Stack.pop();
        }
        return Stack.empty();
    }
};
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
//24.两两交换链表中的节点
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
    ListNode* swapPairs(ListNode* head) {
        // //递归调用
        // if(head==nullptr||head->next==nullptr){
        //     return head;
        // }
        // ListNode* tmp=new ListNode(0);
        // tmp=head->next;
        // head->next=swapPairs(tmp->next);//
        // tmp->next=head;
        // return tmp;
        //迭代法
        if(head==nullptr||head->next==nullptr){
            return head;
        }
        ListNode* dummyhead=new ListNode(0);
        dummyhead->next=head;
        ListNode* tmp=dummyhead;
        while(tmp->next!=nullptr&&tmp->next->next!=nullptr){
            ListNode* one=tmp->next;
            ListNode* two=tmp->next->next;
            tmp->next=two;
            one->next=two->next;
            two->next=one;
            tmp=tmp->next->next;
        }
        return dummyhead->next;
    }
};
//26.删除有序数组中的重复项
class Solution {
public:
//快慢指针
    int removeDuplicates(vector<int>& nums) {
        int n=nums.size();
        if(n==0){
            return 0;
        }
        else{
       int fast=1,slow=1;
       while(fast<n){
           if(nums[fast]!=nums[fast-1]){
                nums[slow]=nums[fast];
                ++slow;
           }
          ++fast;
       }
       return slow;

        }
    }
};
//33.搜索旋转排序数组
class Solution {
public:
    /*二分查找
    如果前半部分有序则取查找前半部分的
        在前半部分区间就让右界减小 否则左界增加
    后半部分则相反*/
    int search(vector<int>& nums, int target) {
        int N=nums.size();
        if(N==0)return -1;
        if(N==1)return nums[0]==target?0:-1;
        int l=0,r=N-1;
        while(l<=r){
            int mid=(l+r)/2;
            if(target==nums[mid])return mid;
            if(nums[0]<=nums[mid]){
                if(nums[0]<=target&&target<nums[mid]){
                    r=r-1;
                }
                else{
                    l=l+1;
                }
            }
            else{
                if(target>nums[mid]&&target<=nums[N-1]){
                    l=l+1;
                }
                else{
                    r=r-1;
                }
            }
        }
        return -1;
    }
};
//34.在排序数组中查找元素的第一个和最后一个位置
class Solution {
public:
//这个方法是遍历数组 时间复杂度为O（N）；
    vector<int> searchRange(vector<int>& nums, int target) {
        int n=nums.size();
        int count=0;
        vector<int>ans;  
        for(int i=0;i<n;++i){
            if(nums[i]==target){
                if(count==0){
                    ans.push_back(i);
                    count++;
                    continue;
                }
                count++;
                }
        }
        if(count==0){
             ans.push_back(-1);
            ans.push_back(-1);
            return ans;
        }
        else{
        ans.push_back(ans.back()+count-1);
        return ans;
        }
    }
};
//35.搜索插入位置
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n=nums.size();
        int left=0,right=n-1;
        int mid;
        while(left<right){
            mid=(left+right)/2;
            if(nums[mid]==target){return mid;}
            if(nums[mid]>target){
                right=mid-1;
            }
            if(nums[mid]<target){
                left=mid+1;
            }
        }
        return target<=nums[left]?left:left+1;
    }
};
//36.有效数独
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int rows[9][9];
        int columns[9][9];
        int little[3][3][9];
        memset(rows,0,sizeof(rows));
        //memset函数 将rows后的xx个字节改为0
        memset(columns,0,sizeof(columns));
        memset(little,0,sizeof(little));
        /*遍历一次，设置三个数组，一个存储每行的情况，一个存储每列的情况，最后一个是三维数组存储小九宫格*/
        //不为，的时候，就在对应位置上加一，最后如果大于1的话就是出现了多次
        //最后注意九宫格 i/3,j/3 对应于九宫格的位置
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                char c=board[i][j];
                if(c!='.'){
                    int index=c-'0'-1;
                    rows[i][index]++;
                    columns[j][index]++;
                    little[i/3][j/3][index]++;
                    if(rows[i][index]>1||columns[j][index]>1||little[i/3][j/3][index]>1){
                        return false;
                    }
                }
            }
        }
    return true;
    }
};
//37.解数独
class Solution {
public:
//标准的回溯算法
    bool backtracking(vector<vector<char>>&board){
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                if(board[i][j]!='.')continue;
                for(char k='1';k<='9';k++){
                    if(isright(i,j,k,board)){
                        board[i][j]=k;
                        if(backtracking(board))return true;
                        board[i][j]='.';
                    } 
                }
                 return false;//数都试完了，没有正确解就返回false
            }
        }
        return true;//遍历整个board没有return false就说明找到合适的解了
    }
    bool isright(int i,int j,char c,vector<vector<char>>&board){
        for(int a=0;a<9;a++)
        {
            if(board[i][a]==c)return false;
        }
        for(int b=0;b<9;b++)
        {
            if(board[b][j]==c)return false;
        }
        int row=(i/3)*3;
        int col=(j/3)*3;
        for(int k=row;k<row+3;k++){
            for(int l=col;l<col+3;l++){
            if(board[k][l]==c)return false;
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);
    }
};
//39.组合总和
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        result.clear();
        path.clear();
        sort(candidates.begin(),candidates.end());
        backtracking(candidates,target,0,0);
        return result;
}
private:
    vector<vector<int>>result;
    vector<int>path;
    void backtracking(vector<int>& candidates,int target,int sum,int current)
    {
       // if(sum>target)return;
        if(sum==target){
               result.push_back(path);
               return ;}
        for(int i=current;i<candidates.size()&&candidates[i]+sum<=target;++i){
            sum+=candidates[i];
            path.push_back(candidates[i]);
            backtracking(candidates,target,sum,i);
            sum-=candidates[i];
            path.pop_back();
        }
    }
};
//40.组合总和Ⅱ
//当candidates元素相等时，如果前一个used=false，则同一树层使用过
//如果used=true，同一树支使用过，避开重复的数组就 当used=false时候跳过此次循环
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target){
        vector<bool>used(candidates.size(),false);
        result.clear();
        path.clear();
        sort(candidates.begin(),candidates.end());
        backtracking(candidates,target,0,0,used);
        return result;
}
private:
    vector<vector<int>>result;
    vector<int>path;
    void backtracking(vector<int>& candidates,int target,int sum,int current,vector<bool>& used)
    {
       // if(sum>target)return;
    
        if(sum==target){
               result.push_back(path);
               return ;}
        for(int i=current;i<candidates.size()&&candidates[i]+sum<=target;++i){
            if(i>0&&candidates[i]==candidates[i-1]&&used[i-1]==false){
           continue;
       }
            sum+=candidates[i];
            path.push_back(candidates[i]);
            used[i]=true;
            backtracking(candidates,target,sum,i+1,used);//i+1可以去掉重复选用同一个数组元素的情况
            sum-=candidates[i];
            path.pop_back();
            used[i]=false;
        }
    }
};
//41.缺失的第一个正数
class Solution {
public:
//主要思想是将每个元素x挪到x-1的位置上，然后遍历数组，第一个不满足条件的就是缺失的第一个正数
    int firstMissingPositive(vector<int>& nums) {
        for(int i=0;i<nums.size();++i){
            while(nums[i]>0&&nums[i]<=nums.size()&&nums[i]!=nums[nums[i]-1]){
                swap(nums[i],nums[nums[i]-1]);
            }
        }
        for(int i=0;i<nums.size();i++){
            if(nums[i]!=1+i){
                return i+1;
            }
        }
      return nums.size()+1;
    }
};
//42.接雨水
class Solution {
public:
/*初始化两个数组，两次循环，一个存储当前位置左侧最大值，另一个存储右侧最大值，
又因为短板效应得到每个位置能接到的雨水，再遍历一遍加起来就是结果*/
    int trap(vector<int>& height) {
        vector<int>left_max(height.size());
        vector<int>right_max(height.size());
        left_max[0]=height[0];
        for(int i=1;i<height.size();i++){
            left_max[i]=max(left_max[i-1],height[i]);
        }
        right_max[height.size()-1]=height[height.size()-1];
        for(int j=height.size()-2;j>=0;j--){
            right_max[j]=max(height[j],right_max[j+1]);
        }
        int ans=0;
        for(int i=0;i<height.size();i++){
            ans=ans+(min(left_max[i],right_max[i])-height[i]);
        }
        return ans;
      }
};
//45.跳跃游戏Ⅱ
class Solution {
public:
    int jump(vector<int>& nums) {
       int n=nums.size();
       int currentdistance=0;
       int nextdistance=0;
       int ans=0;
       if(n==1)return 0;
       else{
           for(int i=0;i<nums.size();++i){
           nextdistance=max(nums[i]+i,nextdistance);
           if(i==currentdistance){
            if(currentdistance!=n-1){
               ans++;
               currentdistance=nextdistance;
               if(nextdistance>=n-1)break;
               }
               else{
                   break;
                   }
           }
       }
    return ans;
    }
    
    }
};
//46.全排列
class Solution {
public:
//回溯问题主要解决思想：纵向递归，横向遍历
   vector<vector<int>>result;
   vector<int>path;
   void backtracking(vector<int>& nums, vector<bool>& used){
       if(path.size()==nums.size())
       {
           result.push_back(path);
           return;
       }
       for(int i=0;i<nums.size();++i){
           if(used[i]==true)continue;
           used[i]=true;
           path.push_back(nums[i]);
           backtracking(nums,used);
           path.pop_back();
           used[i]=false;
       }
   }
    vector<vector<int>> permute(vector<int>& nums) {
       vector<bool>used(nums.size(),false);
       result.clear();
       path.clear();
       backtracking(nums,used);
       return result;
    }
};
//47.全排列Ⅱ
//与46相比本题需要返回所有不重复的全排列
class Solution {
public: 
    vector<vector<int>>result;
   vector<int>path;
   void backtracking(vector<int>& nums, vector<bool>& used){
       if(path.size()==nums.size())
       {
           result.push_back(path);
           return;
       }
       for(int i=0;i<nums.size();++i){
           if(i>0&&nums[i]==nums[i-1]&&used[i-1]==false)continue;
           if(used[i]==false){
           used[i]=true;
           path.push_back(nums[i]);
           backtracking(nums,used);
           path.pop_back();
           used[i]=false;
           }
       }
       }
   vector<vector<int>> permuteUnique(vector<int>& nums) {
   vector<bool>used(nums.size(),false);
       result.clear();
       path.clear();
       sort(nums.begin(),nums.end());
       backtracking(nums,used);
       return result;
   }
   
};
//51.N皇后
class Solution {
public:
    vector<vector<string>>result;
    void backtracking(int n,int row,vector<string>&chessboard){
        if(row==n){
            result.emplace_back(chessboard);
            return ;//如果符合要求则加入result
        }
       for(int col=0;col<n;col++){
           if(iscorrect(col,row,chessboard,n)){
               chessboard[row][col]='Q';
               backtracking(n,row+1,chessboard);
               chessboard[row][col]='.';
           }
       }
    }
    bool iscorrect(int col,int row,vector<string>&chessboard,int n){
        for(int i=0;i<row;i++){
        if(chessboard[i][col]=='Q')return false;//检查列
        }
        for(int i=row-1,j=col-1;i>=0&&j>=0;i--,j--){
            if(chessboard[i][j]=='Q')return false;//检查左上方
        }
        for(int i=row-1,j=col+1;i>=0&&j<n;i--,j++){
            if(chessboard[i][j]=='Q')return false;//检查右下方
        }
        return true;
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<string>chessboard(n,string(n,'.'));//定义n*n的数组
        result.clear();
        backtracking(n,0,chessboard);
        return result;
    }
};
//52.N皇后Ⅱ
class Solution {
public: 
//缺 二进制移位法
    void backtracking(int n,int row,vector<string>&chessboard){
        if(row==n){
            result.emplace_back(chessboard);
            return ;//如果符合要求则加入result
        }
       for(int col=0;col<n;col++){
           if(iscorrect(col,row,chessboard,n)){
               chessboard[row][col]='Q';
               backtracking(n,row+1,chessboard);
               chessboard[row][col]='.';
           }
       }
    }  
    bool iscorrect(int col,int row,vector<string>&chessboard,int n){
        for(int i=0;i<row;i++){
        if(chessboard[i][col]=='Q')return false;//检查列
        }
        for(int i=row-1,j=col-1;i>=0&&j>=0;i--,j--){
            if(chessboard[i][j]=='Q')return false;//检查左上方
        }
        for(int i=row-1,j=col+1;i>=0&&j<n;i--,j++){
            if(chessboard[i][j]=='Q')return false;//检查右下方
        }
        return true;
    }
     vector<vector<string>>result;
    int totalNQueens(int n) {
        vector<string>chessboard(n,string(n,'.'));//定义n*n的数组
        result.clear();
        backtracking(n,0,chessboard);
        return result.size();
    }
 /*int dfs(int n,int row,int colum,int dis1,int dis2){ 
        if(row==n){
            return 1;
        }
        else{ 
            int count=0;
             int aviliable=((1<<n)-1)&(~(colum|dis1|dis2));
        while(aviliable!=0){ 
           int position=aviliable&(-aviliable);
            aviliable=aviliable&(aviliable-1);
           count+=dfs(n,row+1,colum|position,(dis1|position)<<1,(dis2|position)>>1);
        }
          return count;
        }
    }
    int totalNQueens(int n) {
      int ans= dfs(n,0,0,0,0);
       return ans;
    }*/
    
};
//53.最大子数组和
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
    //  vector<int>dp(nums.size(),0);
    //  dp[0]=nums[0];
    //  for(int i=1;i<nums.size();i++){
    //      dp[i]=max(nums[i],dp[i-1]+nums[i]);
    //  }
    //  int res=INT_MIN;
    //  for(int i=0;i<nums.size();i++){
    //      res=max(dp[i],res);
    //  }
    //  return res;
     //省内存写法
     int dp[2]={nums[0],0};
     int res=dp[0];
     for(int i=1;i<nums.size();i++){
         dp[1]=max(nums[i],dp[0]+nums[i]);
         res=max(res,dp[1]);
         dp[0]=dp[1];
     }
     return res;
    }
};
//54.螺旋矩阵
class Solution {
public:
//及时更新每次添加数组的界限，并设定结束循环的条件
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m=matrix.size();
        int n=matrix[0].size();
        int top=0,down=m-1,left=0,right=n-1;
        vector<int>ans;
        while(1){
            if(left>right) break;
            for(int i=left;i<=right;i++){
                ans.push_back(matrix[top][i]);
            }
            top++;
            if(top>down)break;
            for(int i=top;i<=down;i++){
                ans.push_back(matrix[i][right]);
            }
            right--;
            if(left>right)break;
            for(int i=right;i>=left;i--){
                ans.push_back(matrix[down][i]);
            }
            down--;
            if(top>down)break;
            for(int i=down;i>=top;i--){
                ans.push_back(matrix[i][left]);
            }
            left++;
        }
    return ans;
  }
    
};
//55.跳跃游戏
//设定最右侧的值，每次循环进行更新，如果大于数组长度-1，就返回1 否则返回0
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int rightmost=0;
        for(int i=0;i<nums.size();++i){
            if(i<=rightmost){
                rightmost=max(rightmost,nums[i]+i);
                if(rightmost>=nums.size()-1)return true;
            }
        }
         return false;
    }
};
//58.最后一个单词的长度
class Solution {
public:
    int lengthOfLastWord(string s) {
        int i=s.size()-1;
        int count=0;
        while(s[i]==' '){
            --i;
        }
        while(i>=0&&s[i]!=' '){
            ++count;
            --i;
        }
        return count;
    }
};
//62.不同路径
class Solution {
public:
//当前不同路径=左边路径+上边路径，动态规划问题
    int uniquePaths(int m, int n) {
        vector<vector<int>>f(m,vector<int>(n));
            for(int i=0;i<m;++i){
                f[i][0]=1;
            }
            for(int j=0;j<n;j++){
                f[0][j]=1;
            }
            for(int i=1;i<m;i++){
                for(int j=1;j<n;j++){
                    f[i][j]=f[i-1][j]+f[i][j-1];
                }
            }
            return f[m-1][n-1];
    }
};
//63.不同路径Ⅱ
class Solution {
public:
//本题初始化条件与62不同，其次是当无障碍的时候才进行计算，否则跳过此次循环
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.size();
        int n=obstacleGrid[0].size();
        vector<vector<int>>f(m,vector<int>(n));
            for(int i=0;i<m&&obstacleGrid[i][0]==0;++i)
                f[i][0]=1;
            for(int j=0;j<n&&obstacleGrid[0][j]==0;j++){
                f[0][j]=1;
            }
            for(int i=1;i<m;i++){
                for(int j=1;j<n;j++){
                    if(obstacleGrid[i][j]==1)continue;
                    f[i][j]=f[i-1][j]+f[i][j-1];
                }
            }
            return f[m-1][n-1];
    }
};
//64.最小路径和
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        // vector<vector<int>>dp(grid.size(),vector<int>(grid[0].size(),0));
        // dp[0][0]=grid[0][0];
        // for(int i=1;i<grid.size();i++){
        //     dp[i][0]=dp[i-1][0]+grid[i][0];
        // }
        // for(int j=1;j<grid[0].size();j++){
        //     dp[0][j]=dp[0][j-1]+grid[0][j];
        // }
        // for(int i=1;i<grid.size();i++){
        //     for(int j=1;j<grid[0].size();j++)
        //     dp[i][j]=min(dp[i-1][j],dp[i][j-1])+grid[i][j];
        // }
        // return dp[grid.size()-1][grid[0].size()-1];
    //只用一维数组的方法
        vector<int>dp(grid[0].size(),0);
        dp[0]=grid[0][0];
        for(int j=1;j<grid[0].size();j++){
            dp[j]=grid[0][j]+dp[j-1];
        }
        int tmp=grid[0][0];
        for(int i=1;i<grid.size();i++){
            tmp=tmp+grid[i][0]; 
            int t=tmp;
            for(int j=1;j<grid[0].size();j++){
            dp[j]=min(dp[j],t)+grid[i][j];
            t=dp[j];
            }
        }
        return dp[grid[0].size()-1];
    }
};
//66.加一
class Solution {
public:
  //本题主要考虑当遇到999这种情况的时候要一直进位到第一位，此时就需要一个新的数组去存放答案，
  //其他情况都可以在输入数组的原址上进行修改
    vector<int> plusOne(vector<int>& digits) {
       for(int i=digits.size()-1;i>=0;i--)
       {
           digits[i]++;
           digits[i]=digits[i]%10;
           if(digits[i]!=0)
            {return digits;}
       }
    vector<int>ans(digits.size()+1);
    ans[0]=1;
    return ans;
    }
};
//67.二进制求和
class Solution {
public:
    //与415.字符串相加类似
    string addBinary(string a, string b) {
        int carry=0;
        int i=a.size()-1;
        int j=b.size()-1;
        int current=0;
        string ans="";
        while(i>=0||j>=0||carry!=0)//防止产生最高位进位
        {
            int x=i>=0?a[i--]-'0':0;
            int y=j>=0?b[j--]-'0':0;
            current=(x+y+carry);
            carry=current/2;
            ans.push_back('0'+current%2);
        }
        reverse(ans.begin(),ans.end());
        return ans;

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
//70.爬楼梯
class Solution {
public:
    int climbStairs(int n) {
        int q=0,p=0,ans=1;
       for(int i=1;i<=n;i++){
           q=p;
           p=ans;
           ans=p+q;
       }
       return ans;
    }
};
//72.编辑距离
class Solution {
public: 
    int Min(int a,int b,int c){
        return min(a,min(b,c));
    }
    int minDistance(string word1, string word2) {
       vector<vector<int>>dp(word1.size()+1,vector<int>(word2.size()+1,0));
        //dp含义：dp[i][j]返回 word1[0~i] word2[0~j]的最小编辑距离,初始化为0；
        for(int i=1;i<=word1.size();i++){
            dp[i][0]=i;
        }
        for(int j=1;j<=word2.size();j++){
            dp[0][j]=j;
        }
        for(int i=1;i<=word1.size();i++){
            for(int j=1;j<=word2.size();j++){
                if(word1[i-1]==word2[j-1]){dp[i][j]=dp[i-1][j-1];}//注意字符串与dp数组的对应关系
                else{
                    dp[i][j]=Min(
                        dp[i][j-1]+1,//word1尾部插入word2[j]元素,j-1
                        dp[i-1][j]+1,//word1尾部删除word2[j]元素,i-1
                        dp[i-1][j-1]+1//替换为相同的元素 i,j均-1
                    );
                }
            }
        }
    return dp[word1.size()][word2.size()];
    }
};
//75.颜色分类
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left=0;int right=nums.size()-1;
        int index=0;
        while(index<=right){
            if(nums[index]==0){
                swap(nums[left++],nums[index++]);//左右指针分别是0与2的右/左边界
            }
            else if(nums[index]==1)
            {
                index++;
            }
            else{
                swap(nums[index],nums[right--]);
            }
        }
   }
};
//79.单词搜索
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        for(int i=0;i<board.size();i++)
        {
            for(int j=0;j<board[0].size();j++){
               if(backtracking(board,word,0,i,j)){return true;
               }
            }
        }
       return false;
    }
private:
    bool backtracking(vector<vector<char>>&board,string &word,int index,int i,int j){
        if(board[i][j]!=word[index]){return false;}
        if(word.size()-1==index){return true;}
        char tmp=board[i][j];
        board[i][j]=0;
        index=index+1;
        //四个判断 向上向下向左向右递归
        if((i>0&&backtracking(board,word,index,i-1,j))
        ||(i<board.size()-1&&backtracking(board,word,index,i+1,j))
        ||(j>0&&backtracking(board,word,index,i,j-1))
        ||(j<board[0].size()-1&&backtracking(board,word,index,i,j+1))
        ){
            return true;
        }
        board[i][j]=tmp;
        return false;
    }
};
//80.删除排序数组中的重复项Ⅱ
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
       /* 快慢指针，注意一个元素最多存在的次数*/
        if(nums.size()<=2)return nums.size();

        int slow=2;int fast=2;
        while(fast<nums.size()){
            if(nums[fast]!=nums[slow-2]){
                nums[slow]=nums[fast];
                slow++;
            }
           fast++;
        }
        return slow;
    }
};
//82删除排序链表中的重复元素Ⅱ
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

    ListNode* deleteDuplicates(ListNode* head) {
    //     //采用递归调用函数来解决，重点是理解函数的作用
    //    if(head==nullptr||head->next==nullptr)return head;
    //    ListNode *cur=head;
    //        if(cur->val!=cur->next->val){
    //            //相等，对下一节点递归调用函数
    //            cur->next=deleteDuplicates(cur->next);
    //        }
    //        else{
    //            ListNode *nextnode;
    //            nextnode=cur->next;
    //            while(nextnode!=nullptr&&cur->val==nextnode->val){
    //                nextnode=nextnode->next;
    //            }
    //            //不相等，找到不相等的节点，递归调用该节点
    //            return deleteDuplicates(nextnode);
    //        }

    //接下来使用链表性质进行一次遍历来解决问题
    ListNode* Head=new ListNode(0);
    Head->next=head;
    ListNode* pre=Head;
    ListNode* cur=head;
    while(cur!=nullptr){
        while(cur->next!=nullptr&&cur->val==cur->next->val){
            cur=cur->next;
        }
        if(pre->next==cur){
            pre=pre->next;
            //表示pre下一个元素就是cur 中间没有相同元素，则pre后移一位
        }
        else{
            //如果不是紧邻下一位，因为cur指向相同元素的最后一个，pre指向相同元素的前一个，则pre->next应该指向cur->next
            pre->next=cur->next;
        }
        cur=cur->next;
    }
       return Head->next;//返回头节点  新建Head是因为可能会删除头节点
    }
};
//83.删除排序链表中的重复元素
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
//关键点在于while循环的条件，当前节点与下一节点均不为空
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* p=head;
        while(p!=nullptr&&p->next!=nullptr){
            if(p->next->val==p->val){
                p->next=p->next->next;
            }
            else{
            p=p->next;
            }
        }
        return head;
    }
};
//84.柱状图中最大的矩形
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n=heights.size();
        vector<int>left(n);vector<int>right(n);
        stack<int>monoStack;
        int ans=0;
        for(int i=0;i<n;++i){
            while(!monoStack.empty()&&heights[monoStack.top()]>=heights[i]){
                monoStack.pop();
            }
            left[i]=(monoStack.empty()?-1:monoStack.top());
            monoStack.push(i);
        }
        monoStack=stack<int>();
        for(int i=n-1;i>=0;--i){
            while(!monoStack.empty()&&heights[monoStack.top()]>=heights[i])
            {
                monoStack.pop();
            }
            right[i]=(monoStack.empty()?n:monoStack.top());
            monoStack.push(i);
        }
        for(int i=0;i<n;++i){
            ans=max(ans,(right[i]-left[i]-1)*heights[i]);
        }
    return ans;
    }
};
//85.最大矩形
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        vector<int> heights(matrix[0].size(), 0);
        int maxArea = 0;
        for (vector<char>& row : matrix)
        {
            for (int i = 0; i < row.size(); ++ i)
            {
                if (row[i] == '0') heights[i] = 0;  //当前格子为0，则它所在的柱子高度为0
                else heights[i] ++ ;                //格子为1，则它的高度为上一行同位置高度+1
            }
            //每遍历完一行，就计算以这行为基线的直方图最大面积
            maxArea = max(maxArea, largestRectangleArea(heights));
        }
        return maxArea;
    }

    //使用单调栈求直方图最大矩形面积的方法
    //维护一个单调递增的栈
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        stk.push(-1);
        int maxArea = 0;
        for (int i = 0; i < heights.size(); ++ i)
        {
            while (stk.top() != -1 && heights[stk.top()] > heights[i])
            {
                int height = heights[stk.top()];
                stk.pop();
                int width = i - stk.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            stk.push(i);
        }
        while (stk.top() != -1)
        {  
            int height = heights[stk.top()];
            stk.pop();
            int width =heights.size()  - stk.top() - 1;
            //用数组长度减去左边仅次于当前height高度的柱子的位置再-1得到宽度
            maxArea = max(maxArea, height * width);
        }
        return maxArea;
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
//96.不同的二叉搜索树
class Solution {
public:
    int numTrees(int n) {
        //找规律，假设有五个节点，则dp[5]就是 左0*右4+左1右3＋左2右2+左3右1+左4右0
        //动态规划
        vector<int>dp(n+1);
        dp[0]=1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<i;j++){
                dp[i]+=dp[j]*dp[i-1-j];
            }
        }
        return dp[n];
    }
};
//100.相同的树
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==nullptr&&q==nullptr)return true;
        if(p==nullptr||q==nullptr)return false;
        if(q->val!=p->val)return false;
        return isSameTree(p->left,q->left)&&isSameTree(p->right,q->right);
    }
};
//101.对称二叉树
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
class Solution {
public:
    /*如果两个节点都为空，则对称，有一个不为空就不对称，都不为空就看数值是否相等，
    相等时去递归调用，左树的左子节点与右树的右子节点，左数的右子节点与右树的左子节点*/
    bool function(TreeNode *p,TreeNode *q){
        if(q==nullptr&&p==nullptr){
            return true;
        }
        if(q==nullptr||p==nullptr){
            return false;
        }
        if(p->val==q->val){
            return function(p->left,q->right)&&function(p->right,q->left);
        }
        return false;

    }
    bool isSymmetric(TreeNode* root) {
        return function(root,root);
    }
};
//102.二叉树的层序遍历
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 class Solution {
public:
//广度遍历
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector <vector <int>> ret;
        if (!root) {
            return ret;
        }
        queue <TreeNode*> q;
        q.push(root);
        while (!q.empty()) {//只要队列不为空就一直循环
            int currentLevelSize = q.size();//当前队列的大小
            ret.push_back(vector <int> {});//二元数组
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front();//队列中最旧元素
                q.pop();//弹出最旧元素
                ret.back().push_back(node->val);//将元素插入，ret.back是让元素在最新创建的二元数组内插入
                if (node->left) q.push(node->left);//左子树不为空就加入左节点
                if (node->right) q.push(node->right);//右子树不为空就加入右节点
            }
        }
        
        return ret;
    }
};
// class Solution {
// public:
//递归遍历
//    void bianli(TreeNode* root,int depth,vector<vector<int>>&ans){
//        //如果节点为空就返回
//        if(root==nullptr){
//            return ;
//        }
//        if(depth>=ans.size())
//             {//判断层数是否大于数组的大小，如果大于数组的大小则需要扩容
//                 ans.push_back(vector<int>{});
//             }
//        ans[depth].push_back(root->val); //非空节点加入答案
//        bianli(root->left,depth+1,ans);//先遍历左子树，注意层数需要加一
//       bianli(root->right,depth+1,ans);//后遍历右子树。
//    }
//     vector<vector<int>> levelOrder(TreeNode* root) {
//         vector<vector<int>>ans;
//         bianli(root,0,ans);
//         return ans;
//     }
// };
//103.二叉树的锯齿形层序遍历
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>ans;//需要返回的数组
        if(root==nullptr)return ans;
        queue<TreeNode*>NodeQueue;//储存每一层的节点
        bool fangxiang=true;
        //当为真时 在List尾部插入，从左向右遍历，
        //为假时在List头部插入元素,从右向左遍历，
        NodeQueue.push(root);
        while(!NodeQueue.empty()){
            deque<int>List;//储存每一层的val
            int N=NodeQueue.size();
            for(int i=0;i<N;i++){
                auto Node=NodeQueue.front();
                //front()取出最旧的节点
                NodeQueue.pop();//取出后弹出该节点，使用pop()函数
                if(fangxiang){
                    List.push_back(Node->val);
                }else{
                    List.push_front(Node->val);
                }
                if(Node->left){
                    NodeQueue.push(Node->left);
                }
                if(Node->right){
                    NodeQueue.push(Node->right);
                }
            }
            //循环结束后把此次的List放入ans二元数组中
            ans.emplace_back(vector<int>{List.begin(),List.end()});//push back与emplace back的区别在于 emplace添加元素在尾部直接构造，不需要触发拷贝构造与转移构造函数，性能更好一些
            //二元数组的添加数组方法 新建数组，但是不需要写出名字，直接赋予开头与结尾
            fangxiang=!fangxiang;
        }
        return ans;
    }
};
//107.二叉树的层序遍历Ⅱ
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>>ans;
        if(root==nullptr)return ans;//特判
        queue<TreeNode*>NodeQueue;
        NodeQueue.push(root);
        while(!NodeQueue.empty()){ 
            deque<int>List;
            int Size=NodeQueue.size();
            for(int i=0;i<Size;i++){
                auto Node=NodeQueue.front();
                NodeQueue.pop();
                List.push_back(Node->val);
            if(Node->left){
                NodeQueue.push(Node->left);
            }
            if(Node->right){
                NodeQueue.push(Node->right);
            }
            }
            ans.emplace_back(vector<int>{List.begin(),List.end()});
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
//111.二叉树的最小深度
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root==nullptr){
            return 0;
        }
       if(root->left==nullptr){
           //空节点不参与比较
           return 1+minDepth(root->right);
       }
       if(root->right==nullptr){
           return 1+minDepth(root->left);
       }
       return 1+min(minDepth(root->left),minDepth( root->right));

    }
};
//112.路径总和
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root==nullptr){
            return false;
        }
        if(!root->left&&!root->right&&targetSum==root->val){
            return true;
        }
            return hasPathSum(root->left,targetSum-root->val)||hasPathSum(root->right,targetSum-root->val);
    }
};
//113.路径总和Ⅱ
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:  //递归调用，深度遍历
    //     vector<vector<int>>ans;
    //     vector<int>path;
    // void dfs(TreeNode* root,int targetSum){
    //         if(root==nullptr){
    //             return ;
    //         }
    //         path.push_back(root->val);
    //         targetSum=targetSum-root->val;
    //         if(root->left==nullptr&&root->right==nullptr&&targetSum==0){
    //             ans.emplace_back(path);//符合要求的加入ans
    //         }
    //          dfs(root->left,targetSum);
    //          dfs(root->right,targetSum);
    //         path.pop_back();//弹出最新的数组元素
    //     }
    // vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    //     dfs(root,targetSum);
    //     return ans;
    // }
    //广度遍历 广度就是层序 深度是递归，
    vector<vector<int>>ans;
    unordered_map<TreeNode*,TreeNode*>parent;
    void getpath(TreeNode *Node){
        vector<int>path;
        while(Node!=nullptr){
            path.emplace_back(Node->val);
            Node=parent[Node];
        }
        reverse(path.begin(),path.end());
        ans.emplace_back(path);
    }
     vector<vector<int>> pathSum(TreeNode* root, int targetSum){
            if(root==nullptr){return ans;}
            queue<TreeNode*>que_Node;
            queue<int>que_sum;
            que_Node.emplace(root);
            que_sum.emplace(0);
            while(!que_Node.empty()){
                TreeNode *node=que_Node.front();
                que_Node.pop();
                int nums=que_sum.front();
                que_sum.pop();
                nums=nums+node->val;
                if(node->left==nullptr&&node->right==nullptr&&nums==targetSum){
                    getpath(node);
                }
                else{
                    if(node->left!=nullptr){
                        parent[node->left]=node;
                        que_Node.emplace(node->left);
                        que_sum.emplace(nums);
                    }
                    if(node->right!=nullptr){
                        parent[node->right]=node;
                        que_Node.emplace(node->right);
                        que_sum.emplace(nums);
                    }
                }
            }
            return ans;
     }
};
//118.杨辉三角
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>ans(numRows);
        for(int i=0;i<numRows;i++){
            ans[i].resize(i+1);//重新确定子数组的大小
            ans[i][0]=ans[i][i]=1;
            for(int j=1;j<i;j++){
          ans[i][j]=ans[i-1][j-1]+ans[i-1][j];//第i个数组由i-1数组指定两个值相加得到
        }
    }
    return ans;
    }
};
//119.杨辉三角Ⅱ
class Solution {
public:
    vector<int> getRow(int rowIndex) {
       vector<int>cur,pre;
       for(int i=0;i<rowIndex+1;i++){
           cur.resize(i+1);
           cur[0]=cur[i]=1;
           for(int j=1;j<i;j++){
               cur[j]=pre[j-1]+pre[j];
           }
           pre=cur;
       }
        return cur;
    }
};
//120.三角形最小路径
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        //自下向上的
        /*int n=triangle.size();
        int i=n-1;//3
        while(i--){//后置递减 先判断是否进入循环再递减
        //自下向上计算，从倒数第二层开始改变每层的数值为当前数值＋下一层的最小值
            for(int j=0;j<i+1;j++){
                triangle[i][j]+=min(triangle[i+1][j],triangle[i+1][j+1]);
            }
        }
        return triangle[0][0];*/
        //自上向下的
        int n=triangle.size();
        vector<vector<int>>ans(n,vector<int>(n));
        ans[0][0]=triangle[0][0];
        for(int i=1;i<n;i++){
            ans[i][0]=triangle[i][0]+ans[i-1][0];
            for(int j=1;j<i;j++){
                ans[i][j]=min(ans[i-1][j],ans[i-1][j-1])+triangle[i][j];
            }
            ans[i][i]=triangle[i][i]+ans[i-1][i-1];
        }
        return *min_element(ans[n-1].begin(),ans[n-1].end());
    }
};
//121.买卖股票的最佳时机
// class Solution {
// public:
//     int maxProfit(vector<int>& prices) {
//         vector<int>right_max(prices.size());
//         vector<int> ans(prices.size());
//         right_max[prices.size()-1]=prices[prices.size()-1];
//         for(int i=prices.size()-2;i>=0;i--){
//             right_max[i]=max(right_max[i+1],prices[i]);
//         }
//         for(int i=0;i<prices.size();i++){
//             ans[i]=right_max[i]-prices[i];
//         }
//         int a=*max_element(ans.begin(),ans.end());
//         if(a>=0){
//             return a;
//         }
//         else{
//             return 0;
//         }
       
//     }
// };
class Solution{
public:
    int maxProfit(vector<int>&prices){
        int n=prices.size();
        int dp_i_0=0;
        int dp_i_1=INT_MIN;
        for(int i=0;i<n;i++){
            dp_i_0=max(dp_i_0,dp_i_1+prices[i]);
            dp_i_1=max(dp_i_1,-prices[i]);
        }
        return dp_i_0;
    }
};
//122.买卖股票的最佳时机Ⅱ
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        int dp_i_0=0;
        int dp_i_1=INT_MIN;
        for(int i=0;i<n;i++){
            int tmp=dp_i_0;
            dp_i_0=max(dp_i_0,dp_i_1+prices[i]);
            dp_i_1=max(dp_i_1,tmp-prices[i]);
        }
        return dp_i_0;
    }
};
//123.买卖股票的最佳时机Ⅲ
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
       vector<vector<int>>dp(n,vector<int>(5,0));
       //前一个下标为第几天
       //0-4指 0：无操作 1：第一次买 2：第一次卖 3：第二次买 4：第二次卖
       dp[0][1]=dp[0][3]=-prices[0];
        for(int i=1;i<n;i++){
           dp[i][0]=dp[i-1][0];
           dp[i][1]=max(dp[i-1][0]-prices[i],dp[i-1][1]);
           dp[i][2]=max(dp[i-1][1]+prices[i],dp[i-1][2]);
           dp[i][3]=max(dp[i-1][2]-prices[i],dp[i-1][3]);
           dp[i][4]=max(dp[i-1][3]+prices[i],dp[i-1][4]);
        }
        return dp[n-1][4];
    }
};
//125.验证回文串
class Solution {
public:
    bool isPalindrome(string s) {
       int left=0;
       int right=s.length()-1;
       while(left<right){
           while(left<right&&!isalnum(s[left])){
               ++left;
           }
           while(left<right&&!isalnum(s[right])){
               //isalnum():判断字符是否为a-z/A-Z/0-9;是返回1 否则返回0;
               --right;
           }
           if(left<right){
               if(tolower(s[left])!=tolower(s[right])){
                   //tolower将字母转换为小写，对非字母字符不做要求
                   return false;
               }
           else{
               left++;
               right--;
           }
           }
       }
       return true;
    }
};
//129.求根节点到叶子节点数字之和
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans(TreeNode *root,int sum){
        if(root==nullptr)return 0;//如果为空节点返回0;
        if(!root->left&&!root->right)return root->val+10*sum;//遇到叶子节点，返回此时节点的数+sum*10;
        return ans(root->left,10*sum+root->val)+ans(root->right,10*sum+root->val);
    }
    int sumNumbers(TreeNode* root) {
     return ans(root,0);
    }
};
//131.分割回文串
class Solution {
public:
    bool isright(const string &s,int start,int end){
        for(int i=start,j=end;i<j;i++,j--){
            if(s[i]!=s[j]){
              return false;
        }
        }
        return true;
    }
    vector<string>path;
    vector<vector<string>>ans;
    void backtracking(int startindex,string s){
        if(startindex>=s.size()){
            ans.push_back(path);
        }
        for(int i=startindex;i<s.size();i++){
            if(isright(s,startindex,i)){
                string str=s.substr(startindex,i-startindex+1);
                path.push_back(str);
            }else{
                continue;
            }
            backtracking(i+1,s);
            path.pop_back();
        }
    }
    vector<vector<string>> partition(string s) {
        backtracking(0,s);
        return ans;
    }
};
//136.只出现一次的数字
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans=nums[0];
        for(int i=1;i<nums.size();i++){
           ans=ans^nums[i];
        }
        //异或运算，
        //任何数与0异或都是其本身，任何数与自身异或都是0，而且异或可以进行交换律
        //按顺序进行异或，相等的数都变为了0，只出现一次的数最后就是答案
        return ans;
    }
};
//137.只出现一次的数字Ⅱ
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // unordered_map<int,int>hash;
        // int ans;
        // for(int i=0;i<nums.size();++i){ 
        //         hash[nums[i]]++;
        //     }
        // for(int i=0;i<nums.size();i++){
        //     if(hash[nums[i]]!=3){
        //         ans=nums[i];
        //         break;
        //     }
        // }
        // return ans;
        //位运算方法，32位数，将数组中的数逐位相加，
        //因为出现三次的数加起来是3的倍数，所以逐位对3取余数 最后非0的数就是仅出现一次的元素
        int ans=0;
        for(int i=0;i<32;i++){
            int sum=0;
            for(int j=0;j<nums.size();j++){
                sum+=((nums[j]>>i)&1);
            }
            if(sum%3==1){
                    ans=ans|(1<<i);
                }
        }
        return ans;
    }
};
//139.单词拆分
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.size(); i++) {   // 遍历背包
            for (int j = 0; j < i; j++) {       // 遍历物品
                string word = s.substr(j, i - j); //substr(起始位置，截取的个数)
                if (wordSet.find(word) != wordSet.end() && dp[j]) {
                    dp[i] = true;
                }
            }
        }
        return dp[s.size()];
    }
};
//141.环形链表
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
    bool hasCycle(ListNode *head) {
        ListNode *fast=head;
        ListNode *slow=head;
        //因为空链表与单节点链表一定不会有环
        while(fast!=NULL&&fast->next!=NULL){
            fast=fast->next->next;
            slow=slow->next;
            if(fast==slow)return true;
        }
        return false;
    }
};
//142.环形链表Ⅱ
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
    ListNode *detectCycle(ListNode *head) {
        // ListNode *slow=head;
        // ListNode *fast=head;
        // while(fast!=NULL){
        //         slow=slow->next;
        //         if(fast->next==NULL)return NULL;
        //         fast=fast->next->next;
        //         if(slow==fast){
        //             ListNode *p=head;
        //             while(p!=slow){
        //                 slow=slow->next;
        //                 p=p->next;
        //             }
        //             return p;
        //         }
        // }
        // return NULL;
        unordered_set<ListNode*>hash;//hash表 存在当前节点就返回，不存在就新增，遍历结束后就找到了环的入口
        while(head!=NULL){
            if(hash.count(head)){
                return head;
            }
            else{
                hash.emplace(head);
            }
            head=head->next;
        }
        return NULL;
    }
};
//144.二叉树的前序遍历
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int>ans;
    void get(TreeNode* root,vector<int>&ans){
        if(root==nullptr)return ;
        ans.emplace_back(root->val);
        get(root->left,ans);
        get(root->right,ans);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        get(root,ans);
        return ans;
    }
};
//145.二叉树的后序遍历
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int>ans;
    void get(TreeNode* root,vector<int>&ans){
        if(root==nullptr)return ;
        get(root->left,ans);
        get(root->right,ans);
        ans.emplace_back(root->val);
       
    }
    vector<int> postorderTraversal(TreeNode* root) {
        get(root,ans);
        return ans;
    }
};
//160.相交链表
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        //哈希表
        // unordered_set<ListNode*>visited;
        // ListNode* tmp=headA;
        // while(tmp!=NULL){
        //     visited.emplace(tmp);
        //     tmp=tmp->next;
        // }
        // tmp=headB;
        // while(tmp!=NULL){
        //     if(visited.find(tmp)!=visited.end()){
        //         return tmp;
        //     }
        //     tmp=tmp->next;
        // }
        // return NULL;
        //假设链表a长度是 m+c，b是n+c且有交点，则在相遇以前a节点走的路程为m+c+n,b节点走的路程为n+c+m，
        ListNode* a=headA;
        ListNode* b=headB;
       if(headB==NULL||headA==NULL)return NULL;
       while(a!=b){
           a=a==NULL?headB:a->next;
           b=b==NULL?headA:b->next;
       }
       return a;
    }
};
//167.两数之和Ⅱ
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
     //双指针
    //  int left=0;int right=numbers.size()-1;
    //  while(left<right){
    //      int sum=numbers[left]+numbers[right];
    //      if(sum==target){
    //         return {left+1,right+1};
    //      }
    //      else if(sum>target){
    //          right--;
    //      }
    //      else{
    //          left++;
    //      }
    //  }
    //  return {-1,-1};
     //二分查找
     
     for(int i=0;i<numbers.size();i++){
         int left=i+1;int right=numbers.size()-1;
         while(left<=right){
              int mid=(left+right)/2;
            if(numbers[mid]==target-numbers[i])return {i+1,mid+1};
            else if(numbers[mid]>target-numbers[i])right=mid-1;
            else left=mid+1;
         }
     }
     return {-1,-1};
    }
};
//169.多数元素
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        /*int n=nums.size();
        unordered_map<int ,int>hash;
        int ans=0;
        for(int i=0;i<n;i++){
            hash[nums[i]]++;
            if(hash[nums[i]]>n/2){
                ans=nums[i];      
                break;
                }
        }
        return ans;*/
        //投票算法
        //是满足要求的会支持自己，其他人反对 因为终将过半，所以一定会找到正确答案
        int n=nums.size();
        int count=0;
        int ans=-1;
        for(int i=0;i<n;i++){
            if(nums[i]==ans){
                count++;
            }
            else if(--count<0){
                ans=nums[i];
                count=1;
            }
        }
        return ans;
    }
};
//172.阶乘后的零
class Solution {
public:
    int trailingZeroes(int n) {
        //只有2，5相乘才会出现0，又因为2的频率比5高 所以仅计数5的个数
        //n/5+n/25.... 25比5多贡献一个5的因子，一直循环到a>n 
        int ans=0;
        int a=5;
        while(n>=a){
            ans+=(n/a);
            a*=5;
        }
        return ans;
    }
};
//174.地下城游戏
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size(), m = dungeon[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));
        dp[n][m - 1] = dp[n - 1][m] = 1;
        //dp[i][j]表示，从i,j到终点最少需要多少血量
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int minn = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = max(minn - dungeon[i][j], 1);
            }
        }
        return dp[0][0];
    }
};
//179.最大数
class Solution {
public:
   static bool cmp(int a,int b){
       //static修饰函数，静态函数 ，仅在此处可以使用
    string sa=to_string(a);
    string sb=to_string(b);
    return sa+sb>sb+sa;
    }
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end(),cmp);
        string ans;
        for(auto num:nums){
            if(!(num==0&&ans[0]=='0'))ans+=to_string(num);
        }
        return ans;
    }
};
//188.买卖股票的最佳时机Ⅳ
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(prices.size()==0)return 0;
        vector<vector<int>>dp(prices.size(),vector<int>(2*k+1,0));
        //除0以外
        //奇数买入 偶数卖出
        for(int i=1;i<2*k;i+=2){
            dp[0][i]=-prices[0];
        }
        for(int i=1;i<prices.size();i++){
            for(int j=0;j<2*k-1;j+=2){
                dp[i][j+1]=max(dp[i-1][j]-prices[i],dp[i-1][j+1]);
                dp[i][j+2]=max(dp[i-1][j+1]+prices[i],dp[i-1][j+2]);
            }
        }
        return dp[prices.size()-1][2*k];
    }
};
//190.颠倒二进制位
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans=0;
        //新建的一个答案无符号32位 逐位把n的最后一位添加到ans后
        for(int i=0;i<32;i++){
            ans=ans<<1;
            ans+=n&1; //&按位与运算，得到n的最后一位并加在ans的后面
            n=n>>1;
        }
        return ans;
    }
};
//191.位1的个数
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans=0;
        for(int i=0;i<32;i++){
            if(n&1){
                ans++;
                //逐位按位与，如果是1则ans自增 不管是否是1 判断后都需要对n向右移位
                n>>=1;
            }
            else{
                n>>=1;
            }
        }
        return ans;
    }
};
//198.打家劫舍
class Solution {
public:
    int rob(vector<int>& nums) {
        // if(nums.size()==1)return nums[0];
        // vector<int>dp(nums.size(),0);
        // dp[0]=nums[0];
        // dp[1]=max(nums[0],nums[1]);
        // for(int i=2;i<nums.size();i++){
        //     dp[i]=max(dp[i-2]+nums[i],dp[i-1]);
        // }
        // int res=0;
        // for(int i=0;i<nums.size();i++){
        //     res=max(res,dp[i]);
        // }
        // return res;
//省内存写法，仅需要两个int变量
        if(nums.size()==1)return nums[0];
        int first=nums[0],second=max(nums[0],nums[1]);
        for(int i=2;i<nums.size();i++){
            int tmp=second;
            second=max(first+nums[i],second);
            first=tmp;
        }
        return max(second,first);
    }
};
//202.快乐数
class Solution {
public:
    int get_next(int n){
        int next=0;
        while(n>0){
            int nums=n%10;
            next+=nums*nums;
            n=n/10;
        }
        return next;
    }
    bool isHappy(int n) {
       unordered_set<int>hash;//hash集合
        //erase(a);在哈希集occ中删去a
        //insert(a);向哈希集插入a
        //count(a);判断哈希集中是否存在a
        while(!hash.count(n)){
            //哈希表中不存在当前n才进入循环 ，否则返回false
            hash.insert(n);//如果不存在当前n，就插入
            n=get_next(n);//n=当前各位平方取和
            if(n==1){//符合要求的话返回true
                return true;
            }
        }
    return false;
    }
};
//213.打家劫舍Ⅱ
class Solution {
public:
    int robrange(int start,int end,vector<int>nums){
        int first=nums[start],second=max(nums[start+1],nums[start]);
        for(int i=start+2;i<=end;i++){
            int tmp=second;
            second=max(first+nums[i],second);
            first=tmp;
        }
        return max(first,second);

    }
    int rob(vector<int>& nums) {
        if(nums.size()==1||nums.size()==2){
            return nums.size()==1?nums[0]:max(nums[1],nums[0]);
        }
        int n=nums.size();
        //分范围讨论，打劫第一家就跳过最后一家，打劫最后一家就从第二家开始
        return max(robrange(0,n-2,nums),robrange(1,n-1,nums));
    }
};
//219.存在重复元素Ⅱ
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> dictionary;
        int length = nums.size();
        for (int i = 0; i < length; i++) {
            int num = nums[i];
            //如果存在该num,检查是否满足下标要求 满足就返回true
            if (dictionary.count(num) && i - dictionary[num] <= k) {
                return true;
            }
            //不存在或者不满足就继续键值对/不满足下标范围要求的 会更新第二次出现的大的那一个下标
            dictionary[num] = i;//<nums[i],i>将值与下标对应的键值对
        }
        return false;
    }
};
//233.数字1的个数
class Solution {
public:
    // int count(int n){
        //超时写法
    //     int ret=0;
    //     while(n!=0){
    //         int x=n%10;
    //         if(x==1){
    //             ret++;
    //         }
    //         n/=10;
    //     }
    //     return ret;
    // }
    int countDigitOne(int n) {
        // if(n==1)return 1;
        // int ans=0;
        // for(int i=1;i<=n;i++){
        //     ans+=count(i);
        // }
        // return ans;
        long long pow=1;
        int ans=0;
        for(;n>=pow;){
            ans+=(n/(10*pow)*pow+min(max(n%(10*pow)-pow+1,0LL),pow));//0LL是longlong形式下的0
            //分为当前位前 与后，统计1的个数
            pow=pow*10;
        }
        return ans;
    }
 };
//268.丢失得数字
class Solution {
 public:
   int missingNumber(vector<int>& nums) {
//         int ans;
//        vector<bool>a(nums.size()+1,false);
//        for(int i=0;i<nums.size();i++){
//          a [ nums[i]]=true;
//        }
//        for(int i=0;i<a.size();i++){
//            if(a[i]!=true){
//                ans=i;
//                break;
//        }}
//        return ans;
//求和再减
    int cursum=0;
    int sum=0;
    for(int i=0;i<nums.size();i++){
        cursum+=nums[i];
    }
    for(int i=0;i<=nums.size();i++){
        sum+=i;
    }
    return sum-cursum;
    }
 };
// class Solution {
// public:
// //异或所有数后再依次异或[0,n]所剩下得就是第一次没出现得数，即就是答案
//     int missingNumber(vector<int>& nums) {
//         int res = 0;
//         int n = nums.size();
//         for (int i = 0; i < n; i++) {
//             res ^= nums[i];
//         }
//         for (int i = 0; i <= n; i++) {
//             res ^= i;
//         }
//         return res;
//     }
// };
//300.最长递增子序列
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int>dp(nums.size(),1);
        for(int i=0;i<nums.size();i++){
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }
        }
        int ans=0;
        for(int i=0;i<nums.size();i++){
            ans=max(ans,dp[i]);
        }
     return ans;
    }
};
//309.最佳买卖股票时机含冷冻期
class Solution {
public:
    int maxProfit(vector<int>& prices) {
      /*状态0：持有股票-要么昨天已经持有股票未操作，要么今天购入股票
        状态1：早已卖出股票-已经卖出股票且不在冷冻期，一直没操作
        状态2：今天卖出股票-也就是说昨天一定是持有股票的状态
        状态3：冷冻期-昨天卖出了股票*/
        int n=prices.size();
        if(n==0)return 0;
        vector<vector<int>>dp(prices.size(),vector<int>(4,0));
        dp[0][0]=-prices[0];
        for(int i=1;i<prices.size();i++){
            dp[i][0]=max(dp[i-1][0],max(dp[i-1][1],dp[i-1][3])-prices[i]);
                        /*前一天持有股票*//*今天买入是两个状态，1。昨天非冷冻期-状态1，2.昨天是冷冻期-状态3*/
            dp[i][1]=max(dp[i-1][1],dp[i-1][3]);//要么昨天就是这状态，要么昨天刚冷冻期结束
            dp[i][2]=dp[i-1][0]+prices[i];
            dp[i][3]=dp[i-1][2];//冷冻期的前一天一定是卖了股票的
        }
        return max(dp[n-1][1],max(dp[n-1][2],dp[n-1][3]));
    }
};
//322.零钱兑换
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int>dp(amount+1,amount+1);
        dp[0]=0;
        for(int i=0;i<dp.size();i++){
            for(auto coin:coins){
                if(i-coin<0){continue;}
                dp[i]=min(dp[i],dp[i-coin]+1);
            }

        }
        return dp[amount]==amount+1?-1:dp[amount];//判断是否有解
    }
};
//337.打家劫舍Ⅲ
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int rob(TreeNode* root) {
        vector<int> result = robTree(root);
        return max(result[0], result[1]);
    }
    // 长度为2的数组，0：不偷，1：偷
    vector<int> robTree(TreeNode* cur) {
        if (cur == NULL) return vector<int>{0, 0};
        vector<int> left = robTree(cur->left);
        vector<int> right = robTree(cur->right);
        // 偷cur
        int val1 = cur->val + left[0] + right[0];
        // 不偷cur
        int val2 = max(left[0], left[1]) + max(right[0], right[1]);
        return {val2, val1};
    }
};
//343.整数拆分
class Solution {
public:
    int integerBreak(int n) {
        vector <int> dp(n + 1);
        dp[2]=1;
        for (int i = 3; i <= n; i++) {
            int curMax = 0;
            for (int j = 1; j < i; j++) {
                curMax =max(curMax, max(j*(i - j), j*dp[i - j]));
            }
            dp[i] = curMax;
        }
        return dp[n];
    }
};
//415.字符串相加
class Solution {
public:
    string addStrings(string num1, string num2) {
        int carry=0;
        int i=num1.size()-1;
        int j=num2.size()-1;
        int current=0;
        string ans="";
        while(i>=0||j>=0||carry!=0)//防止产生最高位进位
        {
            int x=i>=0?num1[i--]-'0':0;
            int y=j>=0?num2[j--]-'0':0;
            current=(x+y+carry);
            carry=current/10;
            ans.push_back('0'+current%10);
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
//416.分割等和子集
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum=0;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
        }
        if(sum%2==1)return false;
        int target=sum/2;
        vector<int>dp(10001,0);
        for(int i=0;i<nums.size();i++){
            for(int j=target;j>=nums[i];j--){
                dp[j]=max(dp[j],nums[i]+dp[j-nums[i]]);
            }
        }
        if(dp[target]==target) return true;
        return false;
    }
};
//509.斐波那契数
class Solution {
public:
    int fib(int n) {
        if(n<=1)return n;
        int dp[2];
        dp[0]=0;dp[1]=1;
        for(int i=2;i<=n;i++){
            int sum=dp[0]+dp[1];
            dp[0]=dp[1];
            dp[1]=sum;
        }
return dp[1];
    }
};
//516.最长回文子序列
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        // int n=s.size();
        // vector<vector<int>>dp(n,vector<int>(n,0));
        // for(int k=0;k<n;k++){
        //     dp[k][k]=1;
        // }
        // //仅使用上三角数组，i<j
        // for(int i=n-1;i>=0;i--){
        //     for(int j=i+1;j<n;j++){
        //         if(s[i]==s[j]){
        //             dp[i][j]=dp[i+1][j-1]+2;
        //         }
        //         else{
        //             dp[i][j]=max(dp[i+1][j],dp[i][j-1]);
        //         }
        //     }
        // }
        // return dp[0][n-1];
    //压缩为一维数组
          int n=s.size();
        vector<int>dp(n,1);
        for(int i=n-1;i>=0;i--){
            int pre=0;
            for(int j=i+1;j<n;j++){
                int tmp=dp[j];
                if(s[i]==s[j]){
                    dp[j]=pre+2;
                }
                else{
                    dp[j]=max(dp[j],dp[j-1]);
                }
                pre=tmp;
            }
        }
        return dp[n-1];
    }
};
//518.零钱兑换Ⅱ
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int m=coins.size();
        int n=amount;
        //dp含义：用前i个金币凑j的金额 一共有多少方法
        vector<vector<int>>dp(m+1,vector<int>(n+1));
        for(int i=0;i<=m;i++){
            dp[i][0]=1;
        }
        for(int i=0;i<=n;i++){
            dp[0][i]=0;
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(j-coins[i-1]>=0){
                    dp[i][j]=dp[i-1][j]+dp[i][j-coins[i-1]];
                }
                else{
                    dp[i][j]=dp[i-1][j];
                }
            }
        }
        return dp[m][n];
    }
};
//714.买卖股票的最佳时机含手续费
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        if(prices.size()==0)return 0;
        vector<vector<int>>dp(prices.size(),vector<int>(2,0)); 
        dp[0][0]=-prices[0];
        for(int i=1;i<prices.size();i++){
            //状态0持股，1不持股
                dp[i][0]=max(dp[i-1][1]-prices[i],dp[i-1][0]);
                dp[i][1]=max(dp[i-1][0]+prices[i]-fee,dp[i-1][1]);
        }
        return dp[prices.size()-1][1];
    }
};
//950.按递增顺序显示卡牌
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
      sort(deck.begin(), deck.end());
        deque<int>start;
        deque<int>ans;
        vector<int>ret;
        for (int i = 0; i < deck.size(); i++) {
            start.push_back(deck[i]);
        }
        while (!start.empty()) {
            if (ans.empty()) { 
                ans.push_back(start.back()); 
                start.pop_back();
            }
            int tmp = ans.back();  
            ans.push_front(tmp);
            ans.pop_back();
           if( start.empty()){//单独输入1时 不能通过
               break;
               }else{
                   ans.push_front(start.back());
                   }
            start.pop_back();
            }
        while (!ans.empty()) {
            ret.push_back(ans.front());
            ans.pop_front();
        }
        return ret;
    }
};
//971.翻转二叉树以匹配先序遍历
class Solution {
public: 
    vector<int>ans;
    int index=0;
    bool dfs(TreeNode *root,vector<int>& voyage){
       if(root==nullptr)return true;
       int v=root->val;
       if(v!=voyage[index])return false; 
       index++;
       bool left=dfs(root->left,voyage);
       bool right=false;
       if(left){
           right=dfs(root->right,voyage);
       }
       if(!left||!right){
           left=dfs(root->right,voyage);
           right=dfs(root->left,voyage);
           if(!left||!right){
               return false;
           }
           ans.push_back(root->val);
       }
       return true;
    }
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
       if(dfs(root,voyage))return ans;
       else return {-1};
    }
};
//1143.最长公共子序列
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m=text1.size();int n=text2.size();
        vector<vector<int>>dp(m+1,vector<int>(n+1,0));
        //dp[i][j]是text1[0~i] text2[0~j]的最长公共子序列长度
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(text1[i-1]==text2[j-1]){
                    dp[i][j]=dp[i-1][j-1]+1;//字符相等就+1
                }else{
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                    //不相等的话就看末位字符是否与另一字符串的其他位相等，找大的那一个dp值
                }
            }
        }
        return dp[m][n];
    }
};
//1827.最少操作使数组递增
class Solution {
public:
    //超时写法
    // bool isincrease(vector<int>&nums,int n){
    //     if(nums[n]<nums[n+1])return true;
    //     else return false;
    // }
    // int minOperations(vector<int>& nums) {
    //     int count=0;
    //     for(int i=0;i<nums.size()-1;i++){
    //         while(!isincrease(nums,i))
    //         {
    //             nums[i+1]++;
    //             count++;
    //         }
    //     }
    //     return count;
    // }
    
     int minOperations(vector<int>& nums) {
          int ans=0;
         for(int i=1;i<nums.size();i++){
             if(nums[i]<=nums[i-1]){
	//注意是得到递增的次数，不是逐次递增
                 ans+=(nums[i-1]-nums[i]+1);
                 nums[i]=nums[i-1]+1;
                 
             }
         }  
        return ans;
     }
};
//1946.子字符串突变后可能得到的最大整数
class Solution {
public:
    string maximumNumber(string num, vector<int>& change) {
        for(int i=0;i<num.size();i++){
            if(change[num[i]-'0']>num[i]-'0'){
                while(i<num.size()&&change[num[i]-'0']>=num[i]-'0'){
                    num[i]=change[num[i]-'0']+'0';
                    i++;
                }
                break;
            }
        }
        return num;
    }
};
