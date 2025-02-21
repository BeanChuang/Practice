class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // find the minimum road connected with city 1
        vector<vector<pair<int, int>>> g(n);
        for (auto& road : roads) {
            int a = road[0] - 1, b = road[1] - 1, d = road[2];
            g[a].emplace_back(b, d);
            g[b].emplace_back(a, d);
        }

        vector<bool> vis(n);
        auto dfs = [&](this auto&& dfs, int x) -> int {
            vis[x] = true;
            int res = INT_MAX;
            for (auto& [y, d] : g[x]) {
                res = min(res, d);
                if (!vis[y]) {
                    res = min(res, dfs(y));
                }
            }
            return res;
        };
        return dfs(0);
    }
};