class Solution {
public:
    struct Node {
        long long score;
        vector<int> ids;
    };

    bool better(const Node& a, const Node& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.ids < b.ids;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<int, 4>> a(n);

        for (int i = 0; i < n; ++i)
            a[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};

        sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
            if (x[0] != y[0])
                return x[0] < y[0];
            if (x[1] != y[1])
                return x[1] < y[1];
            return x[3] < y[3];
        });

        vector<int> starts(n);
        for (int i = 0; i < n; ++i)
            starts[i] = a[i][0];

        vector<int> next(n);

        for (int i = 0; i < n; ++i) {
            next[i] = upper_bound(starts.begin(), starts.end(), a[i][1]) - starts.begin();
        }

        vector<array<Node, 5>> dp(n + 1);

        for (int cnt = 0; cnt <= 4; ++cnt)
            dp[n][cnt] = {0, {}};

        for (int i = n - 1; i >= 0; --i) {
            for (int cnt = 0; cnt <= 4; ++cnt) {
                Node skip = dp[i + 1][cnt];
                Node take = {-1, {}};

                if (cnt > 0) {
                    take = dp[next[i]][cnt - 1];
                    take.score += a[i][2];
                    take.ids.push_back(a[i][3]);
                    sort(take.ids.begin(), take.ids.end());
                }

                dp[i][cnt] = better(take, skip) ? take : skip;
            }
        }

        return dp[0][4].ids;
    }
};