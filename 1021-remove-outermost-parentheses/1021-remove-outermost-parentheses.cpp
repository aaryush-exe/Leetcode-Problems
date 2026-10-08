class Solution {
public:
    string removeOuterParentheses(string s) {
        string ans = "";
        int depth = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                if (depth > 0)
                    ans += s[i];
                depth++;
            } else {
                depth--;
                if (depth > 0)
                    ans += s[i];
            }
        }
        return ans;
    }
};