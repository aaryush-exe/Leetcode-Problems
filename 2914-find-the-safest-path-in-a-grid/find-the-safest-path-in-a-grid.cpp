class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
         int n = grid.size();
        int N = n * n;

        vector<int> dist(N, -1);
        queue<int> q;

        // Multi-source BFS
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    int id = i * n + j;
                    dist[id] = 0;
                    q.push(id);
                }
            }
        }

        static const int dr[4] = {-1, 1, 0, 0};
        static const int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            int id = q.front();
            q.pop();

            int r = id / n;
            int c = id % n;

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    int nid = nr * n + nc;
                    if (dist[nid] == -1) {
                        dist[nid] = dist[id] + 1;
                        q.push(nid);
                    }
                }
            }
        }

        vector<pair<int,int>> cells;
        cells.reserve(N);
        for (int i = 0; i < N; i++)
            cells.push_back({dist[i], i});

        sort(cells.begin(), cells.end(),
             [](const auto &a, const auto &b) {
                 return a.first > b.first;
             });

        vector<int> parent(N), sz(N, 1);
        iota(parent.begin(), parent.end(), 0);

        auto find = [&](int x) {
            while (parent[x] != x) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        };

        auto unite = [&](int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return;
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
        };

        vector<char> active(N, 0);

        for (auto &[safe, id] : cells) {
            active[id] = 1;

            int r = id / n;
            int c = id % n;

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    int nid = nr * n + nc;
                    if (active[nid])
                        unite(id, nid);
                }
            }

            if (active[0] && active[N - 1] &&
                find(0) == find(N - 1))
                return safe;
        }

        return 0;
    }
};