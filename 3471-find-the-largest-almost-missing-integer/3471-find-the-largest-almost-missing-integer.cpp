class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        int n = nums.size();

        for (int i = 0; i <= n - k; i++) {
            unordered_set<int> seen;

            for (int j = i; j < i + k; j++) {
                seen.insert(nums[j]);
            }

            for (int x : seen) {
                cnt[x]++;
            }
        }

        int ans = -1;

        for (auto &[x, freq] : cnt) {
            if (freq == 1) {
                ans = max(ans, x);
            }
        }

        return ans;
    }
};
