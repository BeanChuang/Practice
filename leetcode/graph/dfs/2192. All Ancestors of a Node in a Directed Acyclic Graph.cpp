class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        // dfs each node once
        // TC : O(n * (n + m)), SC : O(n + m), where m is length of edges

        vector<vector<int>> ans(n);
        vector<vector<int>> g(n);

        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
        }
        
        vector<int> vis(n, -1);
        auto dfs = [&](this auto&& dfs, int src, int x) -> void {
            vis[x] = src;
            for (int y : g[x]) {
                if (vis[y] != src) {
                    ans[y].push_back(src);
                    dfs(src, y);
                }
            }
        };
        for (int i = 0; i < n; i++) {
            dfs(i, i);
        }
        return ans;
    }
};