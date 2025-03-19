class Solution {
public:
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& values) {
        // 1. dfs(x, fa) : max score s.t. the subtree rooted at x is health after opertions
        // 2. tot[x] : sum of node except node 'x'
        // 3. dfs(x, fa) = tot[x] if we not pick up node 'x'
        //                 dfs(y, x) if we pich node x
        // 4. reverse thinking
        //    => dfs(x, fa) : min lost score s.t. the subtree rooted at x is health 
        //    => answer would be sum of values - dfs(root, -1)
        //    => benefit : no need to calculate sum of each subtree.
        // TC : O(n), SC : O(n)
        int n = values.size();
        vector<vector<int>> g(n);
        g[0].push_back(-1); // distinguish root node and leaf node
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        auto dfs = [&](this auto&& dfs, int x, int fa) -> long long {
            if (g[x].size() == 1) {
                return values[x];
            }
            long long lost = 0;
            for (int y : g[x]) {
                if (y != fa) {
                    lost += dfs(y, x);
                }
            }
            return min(lost, (long long) values[x]);
        };
        return reduce(values.begin(), values.end(), 0LL) - dfs(0, -1);
    }
};