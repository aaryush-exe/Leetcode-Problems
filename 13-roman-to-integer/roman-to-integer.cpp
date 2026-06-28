class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> value = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };

        int ans = 0;
        int prev = 0;

        for (int i = s.size() - 1; i >= 0; i--) {
            if (value[s[i]] < prev)
                ans -= value[s[i]];
            else
                ans += value[s[i]];

            prev = value[s[i]];
        }

        return ans;
    }
};