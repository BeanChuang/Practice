class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        // add query[i] edge to graph and bfs the shortest path ansi
        // TC : O(m^2), SC : O(n + m)
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i++) {
            g[i].push_back(i + 1);
        }
        
        vector<int> vis(n, -1);
        auto bfs = [&](int i) -> int {
            queue<pair<int, int>> q;
            q.emplace(0, 0);
            for (;;) {
                auto [x, d] = q.front();
                if (x == n - 1) {
                    return d;
                }
                vis[x] = i;
                q.pop();
                for (int y : g[x]) {
                    if (vis[y] != i) {
                        q.emplace(y, d + 1);
                    }
                }
            }
        };
        
        int m = queries.size();
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            g[queries[i][0]].push_back(queries[i][1]);
            ans[i] = bfs(i);
        }
        return ans;
    }
};