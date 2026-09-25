class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0, litter = 0;
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } else if (classroom[i][j] == 'L') {
                    id[i][j] = litter++;
                }
            }
        }

        int fullMask = (1 << litter) - 1;

        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(n, vector<int>(1 << litter, -1))
        );

        queue<array<int, 4>> q;
        q.push({sr, sc, 0, energy});
        best[sr][sc][0] = energy;

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};
        int moves = 0;

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                auto [r, c, mask, power] = q.front();
                q.pop();

                if (mask == fullMask)
                    return moves;

                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X' || power == 0)
                        continue;

                    int nextPower = power - 1;
                    int nextMask = mask;

                    if (classroom[nr][nc] == 'L')
                        nextMask |= 1 << id[nr][nc];

                    if (classroom[nr][nc] == 'R')
                        nextPower = energy;

                    if (nextPower <= best[nr][nc][nextMask])
                        continue;

                    best[nr][nc][nextMask] = nextPower;
                    q.push({nr, nc, nextMask, nextPower});
                }
            }

            ++moves;
        }

        return -1;
    }
};