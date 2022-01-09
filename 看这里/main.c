//1.两数之和
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
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<int>right_max(prices.size());
        vector<int> ans(prices.size());
        right_max[prices.size()-1]=prices[prices.size()-1];
        for(int i=prices.size()-2;i>=0;i--){
            right_max[i]=max(right_max[i+1],prices[i]);
        }
        for(int i=0;i<prices.size();i++){
            ans[i]=right_max[i]-prices[i];
        }
        int a=*max_element(ans.begin(),ans.end());
        if(a>=0){
            return a;
        }
        else{
            return 0;
        }
       
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
