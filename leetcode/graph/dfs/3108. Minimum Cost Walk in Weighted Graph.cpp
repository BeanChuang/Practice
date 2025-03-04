class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        /// The more weights that perform a bitwise AND operation, the smaller the resulting value.
        // For a query (si, ti):
        // - If si and ti are connected, the minimum cost is the bitwise AND of all connected nodes including si and ti.
        // - Otherwise, return -1.

        // TC : O(n + m + k), SC : O(n + m)
        
        int m = edges.size();
        vector<vector<pair<int, int>>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        
        vector<int> group(n, -1);
        vector<int> res;
        auto dfs = [&](this auto&& dfs, int x, int src) -> int {
            group[x] = src;
            int v = -1;
            for (auto& [y, w] : g[x]) {
                v &= w;
                if (group[y] < 0) {
                    v &= dfs(y, src);
                }
            }
            return v;
        };

        for (int i = 0; i < n; i++) {
            if (group[i] < 0) {
                res.push_back(dfs(i, res.size()));
            }
        }

        int k = query.size();
        vector<int> ans(k, -1);
        for (int i = 0; i < k; i++) {
            int s = query[i][0], t = query[i][1];
            if (group[s] == group[t]) {
                ans[i] = res[group[s]];
            }
        }
        return ans;
    }
};