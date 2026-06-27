class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> count;
        for (int x : nums) {
            count[x]++;
        }

        int max_len = 0;

        // 1. Handle the special case for 1
        if (count.count(1)) {
            int ones = count[1];
            // We need an odd number of 1s to form a valid pattern
            if (ones % 2 == 0) ones--;
            max_len = ones;
        }

        // 2. Handle numbers > 1
        for (auto const& [x, freq] : count) {
            if (x == 1) continue;

            long long curr = x;
            int length = 0;

            // Follow the chain: x, x^2, x^4...
            // As long as we have at least 2 of the current number, 
            // we can continue the chain (one for ascent, one for descent)
            while (count.count(curr) && count[curr] >= 2) {
                length += 2;
                curr *= curr;
            }

            // After the loop, check if there's one more element for the peak
            if (count.count(curr)) {
                length += 1;
            } else {
                // If we stopped because we didn't have the next square,
                // the last '2' we counted was actually a peak.
                // e.g., if we had [2, 4, 4] and no 16.
                length -= 1;
            }

            max_len = max(max_len, length);
        }

        return max_len;
    }
};