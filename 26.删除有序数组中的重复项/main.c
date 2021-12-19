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
