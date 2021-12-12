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
