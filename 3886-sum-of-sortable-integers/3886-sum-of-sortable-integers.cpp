class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefMax(n + 1, 0);
        vector<int> suffMin(n + 1, 1000000000);
        vector<int> prefDrop(n, 0);
        for (int i = 0; i < n; i++) {
            prefMax[i + 1] = max(prefMax[i], nums[i]);
        }
        for (int i = n - 1; i >= 0; i--) {
            suffMin[i] = min(nums[i], suffMin[i + 1]);
        }
        for (int i = 1; i < n; i++) {
            prefDrop[i] = prefDrop[i - 1] + (nums[i - 1] > nums[i]);
        }
        auto check = [&](int k) -> bool {
            for (int start = 0; start < n; start += k) {
                int end = start + k - 1;
                int drops = prefDrop[end] - prefDrop[start];
                if (nums[end] > nums[start]) {
                    drops++;
                }
                if (drops > 1 || prefMax[start] > suffMin[start]) {
                    return false;
                }
            }
            return true;
        };
        int ans = 0;
        for (int k = 1; k <= n / k; k++) {
            if (n % k == 0) {
                if (check(k)) {
                    ans += k;
                }
                int other = n / k;
                if (other != k && check(other)) {
                    ans += other;
                }
            }
        }
        return ans;
    }
};