class Solution {
public:
    int countSpecialSubsequences(vector<int>& nums) {
        // f[i][j] : number of subsequence in nums[0, i - 1] end at value j, where 0 <= j < 3
        // f[i][x] = 2 * f[i - 1][x] + f[i - 1][x - 1], where x = nums[i - 1] 
        // f[i][j] = f[i - 1][j] if j != x
        // initialize f[0][-1] = 1
        // answer is f[n][2].

        // TC : O(n), SC : O(1)
        const int MOD = 1'000'000'007;
        int n = nums.size();
        array<int, 3> f{};
        for (int i = 0; i < n; i++) {
            for (int j = 2; j >= 0; j--) {
                if (nums[i] == j) {
                    f[j] = (2LL * f[j] + (j > 0 ? f[j - 1] : 1)) % MOD;
                }
            }
        }
        return f[2];
    }
};