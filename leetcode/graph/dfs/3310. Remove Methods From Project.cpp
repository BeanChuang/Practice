class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // 1. find the suspicious group first
        // 2. check if any of method in suspicious group invoked by non-suspicious one.
        // TC : O(V + E), O(V + E)

        vector<vector<int>> g(n);
        for (auto& e : invocations) {
            int a = e[0], b = e[1];
            g[a].push_back(b);
        }

        vector<bool> suspicious(n);
        auto dfs = [&](this auto&& dfs, int x) -> void {
            suspicious[x] = true;
            for (int y : g[x]) {
                if (!suspicious[y]) {
                    dfs(y);
                }
            }  
        };
        dfs(k);

        vector<int> ans;
        for (auto& e : invocations) {
            int a = e[0], b = e[1];
            if (!suspicious[a] and suspicious[b]) {
                ans.resize(n);
                ranges::iota(ans, 0);
                return ans;
            }
        }

        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) {
                ans.push_back(i);
            } 
        }
        return ans;
    }
};