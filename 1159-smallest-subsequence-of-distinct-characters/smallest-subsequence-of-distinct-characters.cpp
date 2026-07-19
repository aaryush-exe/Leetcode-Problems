class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> freq(26, 0);
        vector<bool> visited(26, false);

        // Count frequency
        for (char c : s)
            freq[c - 'a']++;

        stack<char> st;

        for (char c : s) {
            freq[c - 'a']--;

            // Skip if already included
            if (visited[c - 'a'])
                continue;

            // Maintain lexicographical order
            while (!st.empty() &&
                   st.top() > c &&
                   freq[st.top() - 'a'] > 0) {
                visited[st.top() - 'a'] = false;
                st.pop();
            }

            st.push(c);
            visited[c - 'a'] = true;
        }

        // Convert stack to string
        string ans;
        while (!st.empty()) {
            ans += st.top();
            st.pop();
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};