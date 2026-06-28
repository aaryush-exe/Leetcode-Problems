class Solution {
public:
    int reverse(int x) {
        int i, temp, r=0;
        long long rev=0;
        temp=x;
        while(temp!=0)
                {
                    r=temp%10;
                    rev=rev*10+r;
                    temp/=10;
                }
        if(rev > INT_MAX || rev < INT_MIN)
            return 0;
        else
            return (int)rev;
    }
};