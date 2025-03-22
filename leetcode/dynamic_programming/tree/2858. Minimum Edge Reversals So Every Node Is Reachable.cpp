class Solution {
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        // 1. count the min edge reversals at node 0
        // 2. if edge connect 0 to 1, then the min edge reversals for 1 is cnt[0] + is_path[0][1]
        // TC : O(n), SC : O(n)

        vector<vector<pair<int, int>>> g(n); // u -> (v, cost)
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].emplace_back(v, 0);
            g[v].emplace_back(u, 1);
        }
        
        vector<int> cnt(n);
        vector<int> ans(n);
        auto dfs = [&](this auto&& dfs, int x, int fa) -> void {
            for (auto [y, cost] : g[x]) {
                if (y != fa) {
                    ans[0] += cost;
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);

        auto dfs2 = [&](this auto&& dfs2, int x, int fa) -> void {
            for (auto [y, cost] : g[x]) {
                if (y != fa) {
                    ans[y] = ans[x] + (cost == 0 ? 1 : -1);
                    dfs2(y, x); 
                }
            }
        };
        dfs2(0, -1);
        return ans;
    }
};