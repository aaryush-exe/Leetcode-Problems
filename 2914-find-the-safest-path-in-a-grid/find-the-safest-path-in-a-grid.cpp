class Solution {
public:
    static constexpr int MAXN = 400;
    static constexpr int MAXCELL = MAXN * MAXN;
    static constexpr int MAXDIST = 798;

    int parent[MAXCELL];
    short sz[MAXCELL];
    short dist[MAXCELL];
    bool active[MAXCELL];

    int qr[MAXCELL], qc[MAXCELL];

    inline int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    inline void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;

        if (sz[a] < sz[b]) swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];
    }

    int maximumSafenessFactor(vector<vector<int>>& grid) {

        int n = grid.size();
        int total = n * n;

        memset(dist, -1, total * sizeof(short));
        memset(active, 0, total * sizeof(bool));

        int head = 0, tail = 0;

        // Multi-source BFS initialization
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    int id = i * n + j;
                    dist[id] = 0;
                    qr[tail] = i;
                    qc[tail] = j;
                    tail++;
                }
            }
        }

        static const int dr[4] = {-1, 1, 0, 0};
        static const int dc[4] = {0, 0, -1, 1};

        // Multi-source BFS
        while (head < tail) {
            int r = qr[head];
            int c = qc[head];
            head++;

            int id = r * n + c;
            short d = dist[id];

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if ((unsigned)nr < (unsigned)n &&
                    (unsigned)nc < (unsigned)n) {

                    int nid = nr * n + nc;

                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        qr[tail] = nr;
                        qc[tail] = nc;
                        tail++;
                    }
                }
            }
        }

        // Bucket sort
        vector<int> bucket[MAXDIST + 1];

        for (int id = 0; id < total; id++)
            bucket[dist[id]].push_back(id);

        for (int i = 0; i < total; i++) {
            parent[i] = i;
            sz[i] = 1;
        }

        for (int safe = MAXDIST; safe >= 0; safe--) {

            for (int id : bucket[safe]) {

                active[id] = true;

                int r = id / n;
                int c = id % n;

                for (int k = 0; k < 4; k++) {

                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if ((unsigned)nr < (unsigned)n &&
                        (unsigned)nc < (unsigned)n) {

                        int nid = nr * n + nc;

                        if (active[nid])
                            unite(id, nid);
                    }
                }
            }

            if (active[0] &&
                active[total - 1] &&
                find(0) == find(total - 1))
                return safe;
        }

        return 0;
    }
};