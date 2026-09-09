class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rows;

        for (auto& seat : reservedSeats) {
            rows[seat[0]] |= 1 << seat[1];
        }

        long long ans = 2LL * (n - rows.size());

        int leftMask = 0;
        int middleMask = 0;
        int rightMask = 0;

        for (int i = 2; i <= 5; ++i)
            leftMask |= 1 << i;

        for (int i = 4; i <= 7; ++i)
            middleMask |= 1 << i;

        for (int i = 6; i <= 9; ++i)
            rightMask |= 1 << i;

        for (auto& [row, mask] : rows) {
            bool left = (mask & leftMask) == 0;
            bool middle = (mask & middleMask) == 0;
            bool right = (mask & rightMask) == 0;

            if (left && right)
                ans += 2;
            else if (left || middle || right)
                ans += 1;
        }

        return ans;
    }
};