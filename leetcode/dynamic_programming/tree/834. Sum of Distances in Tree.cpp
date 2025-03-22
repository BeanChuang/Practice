class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        // 1. find the distance of node x to all other nodes.
        // 2. if an edge connects y to x, then ans[y] will be ans[x] - cnt[y] + (n - cnt[y]),
        //    where cnt[i] is number of nodes in subtree root at i
        // 3. dfs node x to get the answer of all other nodes
        // TC : O(n), SC : O(n)

        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int a = e[0], b = e[1];
            g[a].push_back(b);
            g[b].push_back(a);
        }

        vector<int> ans(n);
        vector<int> cnt(n, 1);
        auto dfs = [&](this auto&& dfs, int x, int fa, int d) -> int {
            ans[0] += d;
            for (int y : g[x]) {
                if (y != fa) {
                    cnt[x] += dfs(y, x, d + 1);
                }
            }
            return cnt[x];
        };
        dfs(0, -1, 0);
        
        auto dfs2 = [&](this auto&& dfs2, int x, int fa) -> void {
            for (int y : g[x]) {
                if (y != fa) {
                    ans[y] = ans[x] + n - 2 * cnt[y];
                    dfs2(y, x);
                }
            }
        };
        dfs2(0, -1);

        return ans;
    }
};