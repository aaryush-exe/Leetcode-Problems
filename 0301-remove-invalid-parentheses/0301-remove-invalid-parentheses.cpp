
class Solution {
public:
    unordered_set<string> seen;
    vector<string> ans;
    void backtrack(string& s, int index, int leftRemove, int rightRemove,
                   int balance, string& current) {
        if (index == s.size()) {
            if (leftRemove == 0 && rightRemove == 0 && balance == 0) {
                if (seen.insert(current).second)
                    ans.push_back(current);
            }
            return;
        }
        char c = s[index];

        if (c == '(' && leftRemove > 0) {
            backtrack(s, index + 1, leftRemove - 1, rightRemove,
                      balance, current);
        }

        if (c == ')' && rightRemove > 0) {
            backtrack(s, index + 1, leftRemove, rightRemove - 1,
                      balance, current);
        }
        if (c != '(' && c != ')') {
            current.push_back(c);
            backtrack(s, index + 1, leftRemove, rightRemove,
                      balance, current);
            current.pop_back();
        } else if (c == '(') {
            current.push_back(c);
            backtrack(s, index + 1, leftRemove, rightRemove,
                      balance + 1, current);
            current.pop_back();
        } else if (balance > 0) {
            current.push_back(c);
            backtrack(s, index + 1, leftRemove, rightRemove,
                      balance - 1, current);
            current.pop_back();
        }
    }
    vector<string> removeInvalidParentheses(string s) {
        int leftRemove = 0;
        int rightRemove = 0;
        for (char c : s) {
            if (c == '(') {
                ++leftRemove;
            } else if (c == ')') {
                if (leftRemove > 0)
                    --leftRemove;
                else
                    ++rightRemove;
            }
        }
        string current;
        backtrack(s, 0, leftRemove, rightRemove, 0, current);
        return ans;
    }
};
