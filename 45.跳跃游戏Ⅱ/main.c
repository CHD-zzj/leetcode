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
