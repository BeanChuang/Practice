class Solution {
public:
    long long maxScore(vector<int>& nums, int x) {
        // f[i][j] : max score of visiting nums[:i] with j parity, where 0 <= j <= 1
        // 1 -> odd, 0 -> even
        // if i is even
        // f[i][0] = max(f[i - 1][0], f[i - 1][1] - x) + nums[i]
        // f[i][1] = f[i - 1][1]
        // if i is odd
        // f[i][0] = f[i - 1][0]
        // f[i][1] = max(f[i - 1][0] - x, f[i - 1][1]) + nums[i]
        // we can compress f to one dimension because f[i] depends on f[i - 1].

        // TC : O(n), SC : O(1)
        
        array<long long, 2> f{};
        f[(nums[0] % 2) ^ 1] = -x;
        for (int y : nums) {
            int j = y % 2;
            f[j] = max(f[j], f[j ^ 1] - x) + y;
        }
        return max(f[0], f[1]);

        // int n = nums.size();
        // vector<array<long long, 2>> memo(n, {-1, -1});
        // auto dfs = [&](this auto&& dfs, int i, int p) -> long long {
        //     if (i == n) {
        //         return 0;
        //     }
        //     long long& res = memo[i][p];
        //     if (res != -1) {
        //         return res;
        //     }
            
        //     if (nums[i] % 2 != p) {
        //         return res = dfs(i + 1, p);
        //     }
        //     return res = max(dfs(i + 1, p), dfs(i + 1, p ^ 1) - x) + nums[i]; 
        // };
        // return dfs(0, nums[0] % 2);
    }
};