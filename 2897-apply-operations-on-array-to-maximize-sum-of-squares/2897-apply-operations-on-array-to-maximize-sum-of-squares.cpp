
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1000000007;
        vector<int> bits(31, 0);
        for (int num : nums) {
            for (int b = 0; b < 31; ++b) {
                if (num & (1 << b))
                    bits[b]++;
            }
        }
        long long ans = 0;
        for (int i = 0; i < k; ++i) {
            long long num = 0;
            for (int b = 0; b < 31; ++b) {
                if (bits[b] > 0) {
                    num |= (1LL << b);
                    bits[b]--;
                }
            }
            ans = (ans + num * num) % MOD;
        }
        return ans;
    }
};