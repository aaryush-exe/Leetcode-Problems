
class Solution {
public:
    bool checkValidString(string s) {
        int l= 0;
        int h = 0;

        for (char c : s) {
            if (c == '(') {
                l++;
                h++;
            } else if (c == ')') {
                l--;
                h--;
            } else {
                l--;
                h++;
            }

            if (h < 0)
                return false;

            l = max(l, 0);
        }

        return l == 0;
    }
};