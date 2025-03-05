class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        // use bfs start from node 0 to each node.
        // record the min path end at each node with blue or red.
        // TC : O(R + B + n), SC : O(R + B + n)

        vector<vector<pair<int, int>>> g(n);
        for (auto& e : redEdges) {
            g[e[0]].emplace_back(e[1], 0);
        }
        for (auto& e : blueEdges) {
            g[e[0]].emplace_back(e[1], 1);
        }
        
        vector<array<int, 2>> d(n, {INT_MAX, INT_MAX});
        d[0] = {0, 0};
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        q.emplace(0, 1);
        while (!q.empty()) {
            auto [x, c1] = q.front();
            q.pop();
            for (auto [y, c2] : g[x]) {
                if (c1 == c2) {
                    continue;
                }
                if (d[y][c2] == -1 or d[x][c1] + 1 < d[y][c2]) {
                    d[y][c2] = d[x][c1] + 1;
                    q.emplace(y, c2);
                }
            }
        }

        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            int mn = min(d[i][0], d[i][1]);
            ans[i] = mn == INT_MAX ? -1 : mn;
        }
        return ans;
    }
};