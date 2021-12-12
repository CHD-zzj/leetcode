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
