class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        // 1. find the number of nodes and edges in subgraph
        // 2. it is complete components if (1 + 2 + ... + v - 1) == number of edges 

        // TC : O(V + E), SC : O(V + E)
        
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int a = e[0], b = e[1];
            g[a].push_back(b);
            g[b].push_back(a);
        }

        vector<bool> vis(n);
        auto dfs = [&](this auto&& dfs, int x) -> pair<int, int> {
            int cnt_v = 1;
            int cnt_e = g[x].size();
            vis[x] = true;
            for (int y : g[x]) {
                if (!vis[y]) {
                    auto [v, e] = dfs(y);
                    cnt_v += v;
                    cnt_e += e;
                }
            }
            return {cnt_v, cnt_e};
        };
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                auto [v, e] = dfs(i);
                if (v * (v - 1) == e) {
                    ans++;
                }
            }
        }
        return ans;
    }
};