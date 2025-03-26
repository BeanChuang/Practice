class Solution {
    const int MOD = 1'000'000'007;
    long long qpow(long long x, int n) {
        long long res = 1;
        for (; n; n /= 2) {
            if (n % 2) {
                res = res * x % MOD;
            }
            x = x * x % MOD;
        }
        return res;
    }
public:
    int waysToBuildRooms(vector<int>& prevRoom) {
        // 1. for tree root at 1, then total way started by 1 is n! / n = (n - 1)!
        // 2. then the order of each subtree should start by its root.
        //    => total way is n! / cnt[1] * cnt[2] * ... * cnt[n - 1], where cnt[i] is number of node root at i
        // TC : O(n + logMOD), SC : O(n)
        int n = prevRoom.size();
        long long fac = 1;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            g[prevRoom[i]].push_back(i);
            fac = fac * (i + 1) % MOD;
        }
        
        long long mul = 1;
        auto dfs = [&](this auto&& dfs, int x) -> int {
            int size = 1;
            for (int y : g[x]) {
                size += dfs(y);
            }
            mul = mul * size % MOD;
            return size;
        };
        dfs(0);
        return fac * qpow(mul, MOD - 2) % MOD;
    }
};