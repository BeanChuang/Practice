class Solution {
public:
    int findCircleNum(vector<vector<int>>& g) {
        // TC : O(n), SC : O(n)
        int n = g.size();
        vector<bool> vis(n);
   
        auto dfs = [&](this auto&& dfs, int x) -> void {
            vis[x] = true;
            for (int y = 0; y < n; y++) {
                if (g[x][y] and !vis[y]) {
                    vis[y] = true;
                    dfs(y);
                }
            }
        };

        int ans = 0;
        for (int x = 0; x < n; x++) {
            if (!vis[x]) {
                dfs(x);
                ans++;
            }
        }
        return ans;
    }
};