class Solution {
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        // 1. find the count of valid guess root at 0 (cnt[0])
        // 2. if edge connects 1 to 0 and reroot at 1, 
        //    then update cnt[1] as cnt[0] - is_parent[0][1] + is_parent[1][0]
        // TC : O(n + m), SC : O(n + m)
        int n = edges.size() + 1;
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        unordered_set<long long> is_parent;
        for (auto& guess : guesses) {
            int u = guess[0], v = guess[1];
            is_parent.insert((long long)u << 32 | v);
        }

        auto dfs = [&](this auto&& dfs, int x, int fa) -> int {
            int res = is_parent.count((long long)fa << 32 | x);
            for (int y : g[x]) {
                if (y != fa) {
                    res += dfs(y, x);
                }
            }
            return res;
        };
        
        vector<int> cnt(n);
        cnt[0] = dfs(0, -1);

        auto dfs2 = [&](this auto&& dfs2, int x, int fa) -> void {
            for (int y : g[x]) {
                if (y != fa) {
                    cnt[y] = cnt[x] - is_parent.count((long long)x << 32 | y) +
                                      is_parent.count((long long)y << 32 | x);
                    dfs2(y, x);
                }
            }
        };
        dfs2(0, -1);
        return ranges::count_if(cnt, [&k](int x) { return x >= k; } );
    }
};
