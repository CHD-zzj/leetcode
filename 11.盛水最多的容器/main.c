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
