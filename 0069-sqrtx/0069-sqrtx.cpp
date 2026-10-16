class Solution {
public:
    int mySqrt(int x) {
        if (x < 2)
            return x;
        int i;
        for (i = 1; i <= x / i; i++) {
            if (1LL * i * i == x)
                return i;
        }
        return i - 1;
    }
};