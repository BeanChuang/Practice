class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        // 1. iterate each bomb to figure out how many it can denoate
        // TC : O(n^3), SC : O(n^2)
        
        int n = bombs.size();
        vector<vector<int>> g(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                auto& b1 = bombs[i];
                auto& b2 = bombs[j];
                int x1 = b1[0], y1 = b1[1], r1 = b1[2];
                int x2 = b2[0], y2 = b2[1], r2 = b2[2];
                
                int dx = x1 - x2;
                int dy = y1 - y2;
                if (1LL * r1 * r1 >= 1LL * dx * dx + 1LL * dy * dy) {
                    g[i].push_back(j);
                }
            }
        }

        vector<int> vis(n, -1);
        auto dfs = [&](this auto&& dfs, int x, int src) -> int {
            int res = 1;
            vis[x] = src;
            for (int y : g[x]) {
                if (vis[y] != src) {
                    res += dfs(y, src);
                }
            }
            return res;
        };

        int ans = 1;
        for (int i = 0; i < n; i++) {
            ans = max(ans, dfs(i, i));
        }
        return ans;
    }
};