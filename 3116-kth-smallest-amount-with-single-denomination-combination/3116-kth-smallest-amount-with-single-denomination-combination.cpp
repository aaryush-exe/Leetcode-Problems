class Solution {
public:
    long long gcd(long long a, long long b) {
        while (b) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    long long lcm(long long a, long long b) {
        return a / gcd(a, b) * b;
    }

    long long count(long long x, vector<int>& coins) {
        int m = coins.size();
        long long total = 0;

        for (int mask = 1; mask < (1 << m); ++mask) {
            long long common = 1;
            int bits = 0;
            bool valid = true;

            for (int i = 0; i < m; ++i) {
                if (mask & (1 << i)) {
                    ++bits;
                    common = lcm(common, coins[i]);

                    if (common > x) {
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid)
                continue;

            long long ways = x / common;

            if (bits & 1)
                total += ways;
            else
                total -= ways;
        }

        return total;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1;
        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (count(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};