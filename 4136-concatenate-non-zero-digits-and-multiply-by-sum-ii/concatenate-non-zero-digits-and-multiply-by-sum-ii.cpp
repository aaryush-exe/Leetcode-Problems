class Solution {
public:
    static constexpr int MOD = 1000000007;

    struct Node {
        long long num;
        int sum;
        int cnt;
        Node(long long n = 0, int s = 0, int c = 0)
            : num(n), sum(s), cnt(c) {}
    };

    vector<Node> seg;
    vector<long long> pw;

    Node merge(const Node &L, const Node &R) {
        Node res;
        res.cnt = L.cnt + R.cnt;
        res.sum = L.sum + R.sum;
        res.num = (L.num * pw[R.cnt] + R.num) % MOD;
        return res;
    }

    void build(int idx, int l, int r, const string &s) {
        if (l == r) {
            int d = s[l] - '0';
            if (d == 0)
                seg[idx] = Node(0, 0, 0);
            else
                seg[idx] = Node(d, d, 1);
            return;
        }

        int mid = (l + r) >> 1;
        build(idx << 1, l, mid, s);
        build(idx << 1 | 1, mid + 1, r, s);
        seg[idx] = merge(seg[idx << 1], seg[idx << 1 | 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[idx];

        int mid = (l + r) >> 1;

        if (qr <= mid)
            return query(idx << 1, l, mid, ql, qr);

        if (ql > mid)
            return query(idx << 1 | 1, mid + 1, r, ql, qr);

        return merge(
            query(idx << 1, l, mid, ql, qr),
            query(idx << 1 | 1, mid + 1, r, ql, qr)
        );
    }

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        pw.resize(n + 1);
        pw[0] = 1;
        for (int i = 1; i <= n; i++)
            pw[i] = (pw[i - 1] * 10) % MOD;

        seg.assign(4 * n + 5, Node());

        build(1, 0, n - 1, s);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            Node cur = query(1, 0, n - 1, q[0], q[1]);
            ans.push_back((cur.num * 1LL * cur.sum) % MOD);
        }

        return ans;
    }
};