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
