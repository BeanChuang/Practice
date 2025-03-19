class Solution {
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        // 1. find the longest diameter in each tree
        // 2. the answer will be (d1 + 1) / 2 + (d2 + 1) / 2  + 1
        // TC : O(n + m), SC : O(n + m)
        auto diameter = [](vector<vector<int>>& edges) -> int {
            int n = edges.size() + 1;
            vector<vector<int>> g(n);
            for (auto& e : edges) {
                int u = e[0], v = e[1];
                g[u].push_back(v);
                g[v].push_back(u);
            }

            int res = 0;
            auto dfs = [&](this auto&& dfs, int x, int fa) -> int {
                int max_d = 0;
                for (int y : g[x]) {
                    if (y != fa) {
                        int d = dfs(y, x) + 1;
                        res = max(res, max_d + d);
                        max_d = max(max_d, d);
                    }
                }
                return max_d;
            };
            dfs(0, -1);
            return res;
        };
        
        // case1 : d1 is longer than (d1 + 1) / 2 + (d2 + 1) / 2 + 1
        // case2 : d2 is longer than (d1 + 1) / 2 + (d2 + 1) / 2 + 1
        // case3 : (d1 + 1) / 2 + (d2 + 1) / 2 + 1 is longer than d1 and d2
        int d1 = diameter(edges1);
        int d2 = diameter(edges2);
        return max({d1, d2, (d1 + 1) / 2 + (d2 + 1) / 2 + 1});
    }
};