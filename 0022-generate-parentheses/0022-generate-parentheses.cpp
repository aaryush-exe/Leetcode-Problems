
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string current;

        function<void(int, int)> backtrack = [&](int open, int close) {
            if (current.size() == 2 * n) {
                ans.push_back(current);
                return;
            }

            if (open < n) {
                current.push_back('(');
                backtrack(open + 1, close);
                current.pop_back();
            }

            if (close < open) {
                current.push_back(')');
                backtrack(open, close + 1);
                current.pop_back();
            }
        };

        backtrack(0, 0);
        return ans;
    }
};
