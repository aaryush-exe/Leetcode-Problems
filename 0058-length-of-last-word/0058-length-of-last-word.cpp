class Solution {
public:
    int lengthOfLastWord(string s) {
        int ctr = 0;
        reverse(s.begin(), s.end());
        int i = 0;
        while (i < s.length() && s[i] == ' ') {
            i++;
        }
        while (i < s.length() && s[i] != ' ') {
            ctr++;
            i++;
        }
        return ctr;
    }
};