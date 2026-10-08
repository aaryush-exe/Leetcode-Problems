
class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        int score = 0;

        for (char c : s) {
            if (c == '(') {
                st.push(score);
                score = 0;
            } else {
                score = st.top() + max(2 * score, 1);
                st.pop();
            }
        }

        return score;
    }
};