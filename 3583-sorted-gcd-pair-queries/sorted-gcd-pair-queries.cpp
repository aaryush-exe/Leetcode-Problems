class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<long long> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;

        // cntDiv[g] = numbers divisible by g
        vector<long long> cntDiv(mx + 1, 0);
        for (int g = 1; g <= mx; g++) {
            for (int multiple = g; multiple <= mx; multiple += g) {
                cntDiv[g] += freq[multiple];
            }
        }

        // exactPairs[g] = pairs whose gcd is exactly g
        vector<long long> exactPairs(mx + 1, 0);

        for (int g = mx; g >= 1; g--) {
            long long c = cntDiv[g];
            exactPairs[g] = c * (c - 1) / 2;

            for (int multiple = 2 * g; multiple <= mx; multiple += g) {
                exactPairs[g] -= exactPairs[multiple];
            }
        }

        // Prefix counts over gcd values
        vector<long long> prefix(mx + 1, 0);
        for (int g = 1; g <= mx; g++) {
            prefix[g] = prefix[g - 1] + exactPairs[g];
        }

        vector<int> ans;
        for (long long q : queries) {
            int g = lower_bound(prefix.begin() + 1, prefix.end(), q + 1) - prefix.begin();
            ans.push_back(g);
        }

        return ans;
    }
};