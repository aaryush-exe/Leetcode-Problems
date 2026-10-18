class Solution {
public:
    int digitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> arr;
        for (int i = 0; i < n; ++i) {
            arr.push_back({nums[i], i});
        }
        sort(arr.begin(), arr.end(), [&](const auto& a, const auto& b) {
            int sumA = digitSum(a.first);
            int sumB = digitSum(b.first);
            if (sumA != sumB)
                return sumA < sumB;
            return a.first < b.first;
        });
        vector<bool> visited(n, false);
        int swaps = 0;
        for (int i = 0; i < n; ++i) {
            if (visited[i] || arr[i].second == i)
                continue;
            int j = i;
            int cycleSize = 0;
            while (!visited[j]) {
                visited[j] = true;
                j = arr[j].second;
                ++cycleSize;
            }
            swaps += cycleSize - 1;
        }
        return swaps;
    }
};