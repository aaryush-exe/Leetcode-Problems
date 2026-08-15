class Solution {
    struct Node {
        int l, r;
        int pref, suff, best;

        Node() {}

        Node(int l, int r) : l(l), r(r), pref(1), suff(1), best(1) {}
    };

    vector<Node> tree;
    string s;

    void build(int u, int l, int r) {
        tree[u] = Node(l, r);

        if (l == r)
            return;

        int mid = (l + r) / 2;

        build(u * 2, l, mid);
        build(u * 2 + 1, mid + 1, r);
        pull(u);
    }

    void pull(int u) {
        Node &cur = tree[u];
        Node &left = tree[u * 2];
        Node &right = tree[u * 2 + 1];

        cur.pref = left.pref;
        cur.suff = right.suff;
        cur.best = max(left.best, right.best);

        if (s[left.r] == s[right.l]) {
            int leftLen = left.r - left.l + 1;
            int rightLen = right.r - right.l + 1;

            if (left.pref == leftLen)
                cur.pref += right.pref;

            if (right.suff == rightLen)
                cur.suff += left.suff;

            cur.best = max(cur.best, left.suff + right.pref);
        }
    }

    void update(int u, int l, int r, int idx, char c) {
        if (l == r) {
            s[idx] = c;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(u * 2, l, mid, idx, c);
        else
            update(u * 2 + 1, mid + 1, r, idx, c);

        pull(u);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        this->s = s;

        int n = s.size();
        tree.resize(4 * n);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(tree[1].best);
        }

        return ans;
    }
};