class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > 9 * num)
            return "";
        string ans(num, '0');
        for (int i = 0; i < num && sum > 0; ++i) {
            int digit = min(9, sum);
            ans[i] = char('0' + digit);
            sum -= digit;
        }
        return ans;
    }
};