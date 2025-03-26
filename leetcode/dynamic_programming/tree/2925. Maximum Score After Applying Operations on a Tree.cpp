class Solution {
public:
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& values) {
        // 1. max score s.t. tree is healthy
        //    = min score lost s.t. tree is healthy
        // 2. dfs(x, fa) = min(sum(dfs(y, x)), values[x]) // min score lost s.t. tree is healthy
        // TC : O(n), SC : O(n)

        int n = edges.size() + 1;
        vector<vector<int>> g(n);
        g[0].push_back(-1);
        for (auto& e : edges) {
            int a = e[0], b = e[1];
            g[a].push_back(b);
            g[b].push_back(a);
        }

        // min score lost with tree root at x
        auto dfs = [&](this auto&& dfs, int x, int fa) -> long long {
            if (g[x].size() == 1) {
                return values[x];
            }
            long long res = 0;
            for (int y : g[x]) {
                if (y != fa) {
                    res += dfs(y, x);
                }
            }
            return min(res, (long long) values[x]);
        };
        return reduce(values.begin(), values.end(), 0LL) - dfs(0, -1);
    }
};