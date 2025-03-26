class Solution {
public:
    int maximumPoints(vector<vector<int>>& edges, vector<int>& coins, int k) {
        // dfs(i, j) : max points by applying way2 j times on the parent of i
        // dfs(i, j) = max((coin >> j) - k + dfs(child, j),
        //                 (coin >> (j + 1)) + dfs(child, j + 1))
        // TC : O(nlogU), SC : O(nlogU), where U = max(coins)
        int n = edges.size() + 1;
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int a = e[0], b = e[1];
            g[a].push_back(b);
            g[b].push_back(a);
        }
        
        array<int, 14> init_val;
        ranges::fill(init_val, -1);
        vector memo(n, init_val);
        auto dfs = [&](this auto&& dfs, int i, int j, int fa) -> int {
            int& res = memo[i][j];
            if (res != -1) {
                return res;
            }
            int f0 = (coins[i] >> j) - k;
            int f1 = (coins[i] >> j + 1);
            for (int child : g[i]) {
                if (child != fa) {
                    f0 += dfs(child, j, i);
                    if (j < 13) {
                        // 2^14 >= maximum of coin
                        f1 += dfs(child, j + 1, i);
                    }
                }
            }
            return res = max(f0, f1);
        };
        return dfs(0, 0, -1);
    }
};