class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // 1. find the height of subtree root at node u
        // 2. if edge connects u to v
        //    - root move from u to v => only height of u and v possibly changed
        //    - h_v[u] = max(h_u[i]) + 1, where i != v and there exist edge connects u to i
        //    - update h_u to h_v 
        //      => h_v[v] = max(h_u[v], h_v[u] + 1)   
        // TC : O(n), SC : O(n)
        
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> h(n), min_h(n);

        auto dfs = [&](this auto&& dfs, int x, int fa) -> int {
            int max_h = 0;
            for (int y : g[x]) {
                if (y != fa) {
                    h[y] = dfs(y, x);
                    max_h = max(max_h, h[y] + 1);
                }
            }
            return h[x] = max_h;
        };
        dfs(0, -1);

        min_h[0] = h[0];
        auto dfs2 = [&](this auto&& dfs2, int x, int fa) -> void {
            int max_adj_h = -1, nd_max_adj_h = -1;
            for (int y : g[x]) {
                if (h[y] > max_adj_h) {
                    nd_max_adj_h = max_adj_h;
                    max_adj_h = h[y];
                } else if (h[y] > nd_max_adj_h) {
                    nd_max_adj_h = h[y];
                }
            }

            for (int y : g[x]) {
                if (y != fa) {
                    h[x] = (h[y] == max_adj_h ? nd_max_adj_h : max_adj_h) + 1;
                    min_h[y] = max(h[y], h[x] + 1);
                    dfs2(y, x);
                }
            }
        };
        dfs2(0, -1);

        int m = ranges::min(min_h);
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (min_h[i] == m) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
    