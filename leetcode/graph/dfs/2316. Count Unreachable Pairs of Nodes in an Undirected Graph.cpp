class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        // 1. find the number of nodes in each group => cnt[i]
        // 2. the number of pairs contributed by group i is cnt[i] * (n - cnt[i]).
        //    to avoid duplicate e.g. (i, j) and (j, i).
        //    we only count the iterated pairs so far 
        // TC : O(n + m), SC : O(n + m)
        
        vector<vector<int>> g(n);
        vector<bool> vis(n);

        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        
        auto dfs = [&](this auto&& dfs, int x) -> int {
            vis[x] = true;
            int res = 1;
            for (int y : g[x]) {
                if (!vis[y]) {
                    res += dfs(y);
                }
            }
            return res;
        };

        int acc_nodes = 0;
        long long ans = 0;
        for (int x = 0; x < n; x++) {
            if (!vis[x]) {
                int cnt = dfs(x);
                ans += 1LL * acc_nodes * cnt;
                acc_nodes += cnt;
            }
        }
        return ans;
    }
};