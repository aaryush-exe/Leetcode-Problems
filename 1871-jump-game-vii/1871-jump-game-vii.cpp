class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        vector<bool> dp(n, false);
        dp[0] = true;
        int reachable = 0;
        for (int i = 1; i < n; i++) {
            if (i - minJump >= 0) {
                reachable += dp[i - minJump];
            }
            if (i - maxJump - 1 >= 0) {
                reachable -= dp[i - maxJump - 1];
            }
            dp[i] = (s[i] == '0' && reachable > 0);
        }
        return dp[n - 1];
    }
};