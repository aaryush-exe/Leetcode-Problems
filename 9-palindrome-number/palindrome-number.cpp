class Solution {
public:
    bool isPalindrome(int x) {
        int i,temp,r=0;
        long int rev=0;
        if(x<0)
            return false;
        temp=x;
        while(temp!=0)
        {
            r=temp%10;
            temp/=10;
            rev=rev*10+r;
        }
        if(rev==x)
            return true;
        else
            return false;
    }
};