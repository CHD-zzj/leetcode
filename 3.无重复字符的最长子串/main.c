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
