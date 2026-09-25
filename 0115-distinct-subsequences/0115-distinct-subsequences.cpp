class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size();
        vector<long long> dp(m + 1, 0);

        dp[0] = 1;

        for (char c : s) {
            for (int j = m; j >= 1; --j) {
                if (c == t[j - 1]) {
                    dp[j] += dp[j - 1];
                    dp[j] = min(dp[j], (long long)INT_MAX);
                }
            }
        }

        return dp[m];
    }
};