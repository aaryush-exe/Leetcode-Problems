
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = 1LL * k1 + k2;
        vector<long long> diff(n);
        long long total = 0;
        long long high = 0;

        for (int i = 0; i < n; ++i) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total += diff[i];
            high = max(high, diff[i]);
        }

        if (k >= total)
            return 0;

        long long low = 0;

        while (low < high) {
            long long mid = low + (high - low) / 2;
            long long needed = 0;

            for (long long d : diff) {
                if (d > mid)
                    needed += d - mid;
            }

            if (needed <= k)
                high = mid;
            else
                low = mid + 1;
        }

        long long remaining = k;
        long long ans = 0;

        for (long long& d : diff) {
            if (d > low) {
                remaining -= d - low;
                d = low;
            }
        }

        for (long long& d : diff) {
            if (remaining > 0 && d == low && d > 0) {
                --d;
                --remaining;
            }

            ans += d * d;
        }

        return ans;
    }
};