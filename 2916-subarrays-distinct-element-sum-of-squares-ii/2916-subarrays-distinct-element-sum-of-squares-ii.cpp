class Solution {
    static constexpr long long MOD = 1000000007;
    struct Node {
        long long sum = 0;
        long long squareSum = 0;
        long long lazy = 0;
    };
    vector<Node> tree;
    int n;
    void apply(int node, int left, int right, long long value) {
        long long len = right - left + 1;
        long long add = value % MOD;
        tree[node].squareSum =
            (tree[node].squareSum + 2 * add % MOD * tree[node].sum % MOD
             + len % MOD * add % MOD * add % MOD) % MOD;
        tree[node].sum =
            (tree[node].sum + len % MOD * add) % MOD;
        tree[node].lazy = (tree[node].lazy + add) % MOD;
    }
    void push(int node, int left, int right) {
        if (tree[node].lazy == 0 || left == right)
            return;
        int mid = left + (right - left) / 2;
        long long value = tree[node].lazy;
        apply(node * 2, left, mid, value);
        apply(node * 2 + 1, mid + 1, right, value);
        tree[node].lazy = 0;
    }

    void update(int node, int left, int right, int ql, int qr) {
        if (ql <= left && right <= qr) {
            apply(node, left, right, 1);
            return;
        }
        push(node, left, right);
        int mid = left + (right - left) / 2;
        if (ql <= mid)
            update(node * 2, left, mid, ql, qr);
        if (qr > mid)
            update(node * 2 + 1, mid + 1, right, ql, qr);
        tree[node].sum =
            (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;
        tree[node].squareSum =
            (tree[node * 2].squareSum +
             tree[node * 2 + 1].squareSum) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, Node());
        unordered_map<int, int> last;
        long long answer = 0;
        for (int i = 0; i < n; ++i) {
            int left = 0;
            if (last.count(nums[i]))
                left = last[nums[i]] + 1;
            update(1, 0, n - 1, left, i);
            last[nums[i]] = i;
            answer = (answer + tree[1].squareSum) % MOD;
        }
        return answer;
    }
};