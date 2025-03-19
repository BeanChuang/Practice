class Solution {
public:
    int longestPath(vector<int>& parent, string s) {
        // 1. find the longest path in tree
        // 2. adjacent node can't have same char
        // TC : O(n), SC : O(n)
        int n = parent.size();
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            g[parent[i]].push_back(i);
        }

        int ans = 0;
        auto dfs = [&](this auto&& dfs, int x) -> int {
            int max_d = 0; // the longest path start from node x
            for (int y : g[x]) {
                int d = dfs(y) + 1;
                if (s[x] != s[y]) {
                    ans = max(ans, d + max_d);
                    max_d = max(max_d, d);
                }
            }
            return max_d;
        };
        dfs(0);
        return ans + 1;
    }
};