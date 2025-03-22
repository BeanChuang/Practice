class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        // 1. each node has two status (half, not half)
        // 2. calculate the traversed count of each node
        // 3. find the min price based on count of each node.
        // TC : O(m * n), SC : O(n), where m is trips length

        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> cnt(n);
        auto dfs = [&](this auto&& dfs, int x, int dst, int fa) -> bool {
            if (x == dst) {
                cnt[x]++;
                return true;
            }
            for (int y : g[x]) {
                if (y != fa and dfs(y, dst, x)) {
                    cnt[x]++;
                    return true;
                }
            }
            return false;
        };
        
        for (auto& t : trips) {
            dfs(t[0], t[1], -1);
        }

        auto dfs2 = [&](this auto&& dfs2, int x, int fa) -> array<int, 2> {
            int tot = cnt[x] * price[x];
            array<int, 2> res{tot / 2, tot};
            for (int y : g[x]) {
                if (y != fa) {
                    auto [half, no_half] = dfs2(y, x);
                    res[0] += no_half;
                    res[1] += min(no_half, half);
                }
            }
            return res;
        };
        return ranges::min(dfs2(0, -1));
    }
};
    