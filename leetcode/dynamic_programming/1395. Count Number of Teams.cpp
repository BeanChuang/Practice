class Solution {
public:
    int numTeams(vector<int>& rating) {
        // f[i][j] : number of increasing sequence end at i with length j
        // f[i][j] = f[k][j - 1] + 1 if rating[i] > rating[k], where 0 <= k < i
        // answer is sum of f[i][3], where 0 <= i < n
        
        // TC : O(n^2), SC : O(n)

        int n = rating.size();

        auto solve = [&]() -> int {
            int res = 0;
            vector<array<int, 4>> f(n, {0, 0, 0, 0});
            for (int i = 0; i < n; i++) {
                f[i][1] = 1;
            }

            for (int i = 0; i < n; i++) {
                for (int k = 0; k < i; k++) {
                    if (rating[i] > rating[k]) {
                        for (int j = 1; j <= min(i + 1, 3); j++) {
                                f[i][j] += f[k][j - 1];
                        }
                    }
                }
                res += f[i][3];
            }
            return res;
        };

        int ans = solve();
        ranges::reverse(rating);
        return ans + solve();
    }
};