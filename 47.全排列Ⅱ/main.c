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
