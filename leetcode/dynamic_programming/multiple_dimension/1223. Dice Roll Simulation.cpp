class Solution {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        // dfs(i, j, k) : roll 'i + 1' dices and last dice 'j' with at most 'k + 1' consecutive times.
        // return 1 if i > n means we have rolled n times
        // TC : O(n*6*15*6), SC : O(6*15)
        const int MOD = 1'000'000'007;

        vector f(6, vector(15, 0));
        for (auto& row : f) {
            ranges::fill(row, 1);
        }

        for (int i = 1; i < n; i++) {
            vector new_f(6, vector(15, 0));
            for (int j = 0; j < 6; j++) {
                for (int k = 0; k < rollMax[j]; k++) {
                    int res = 0;
                    for (int d = 0; d < 6; d++) {
                        if (j != d) {
                            res = (res + f[d][rollMax[d] - 1]) % MOD;
                        } else if (k > 0) {
                            res = (res + f[d][k - 1]) % MOD;
                        }
                    }
                    new_f[j][k] = res;
                }
            }
            swap(new_f, f);
        }
        int ans = 0;
        for (int j = 0; j < 6; j++) {
            ans = (ans + f[j][rollMax[j] - 1]) % MOD;
        }
        return ans;

        // vector memo(n, vector(6, vector(15, -1)));
        // auto dfs = [&](this auto&& dfs, int i, int j, int k) -> int {
        //     if (i == 0) {
        //         return 1;
        //     }
        //     int& res = memo[i][j][k];
        //     if (res != -1) {
        //         return res;
        //     }
        //     res = 0;
        //     for (int d = 0; d < 6; d++) {
        //         if (j != d) {
        //             res = (res + dfs(i - 1, d, rollMax[d] - 1)) % MOD;
        //         } else if (k > 0) {
        //             res = (res + dfs(i - 1, d, k - 1)) % MOD;
        //         }
        //     }
        //     return res;
        // };
        
        // int ans = 0;
        // for (int j = 0; j < 6; j++) {
        //     ans = (ans + dfs(n - 1, j, rollMax[j] - 1)) % MOD;
        // }
        // return ans;
    }
};