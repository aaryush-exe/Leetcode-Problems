class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        vector<vector<bool>> pal(n, vector<bool>(n, false));

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (s[i] == s[j] && (j - i <= 1 || pal[i + 1][j - 1]))
                    pal[i][j] = true;
            }
        }

        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1];

            for (int j = 0; j < i; ++j) {
                if (i - j >= k && pal[j][i - 1])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        return dp[n];
    }
};