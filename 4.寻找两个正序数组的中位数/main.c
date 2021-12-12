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
