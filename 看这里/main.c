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
