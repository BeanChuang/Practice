class Solution {
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        // 1. enumerate all possible vertex combinations 
        // 2. cacl its diameter
        // 3. increase count if it is valid subtree
        // TC : O(n * 2^n), SC : O(n)

        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0] - 1, v = e[1] - 1;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> ans(n - 1);
        for (int m = 3; m < 1 << n; m++) {
            if ((m & m - 1) == 0) {
                continue;
            }

            int diameter = 0, vis = 0;
            auto dfs = [&](this auto&& dfs, int x) -> int {
                vis |= 1 << x;
                int max_d = 0;
                for (int y : g[x]) {
                    if (!(vis & 1 << y) and m & 1 << y) {
                        int d = dfs(y) + 1;
                        diameter = max(diameter, max_d + d);
                        max_d = max(max_d, d);
                    }
                }
                return max_d;
            };
            
            dfs(__builtin_ctz(m));
            if (vis == m) {
                ans[diameter - 1]++;
            }
        }
        return ans;
    }
};