class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        // Every node have two choices
        //     - xor with parent node.
        //     - not xor with parent node.
        // There are even nodes xor with k includes 0 nodes
        // => the problem become finding the max sum after xor even nodes with k

        // Define f[i][0] : max sum s.t. nums[0, i] with even xor nodes
        // Define f[i][1] : max sum s.t. nums[0, i] with odd xor nodes
        // f[i][0] = f[i - 1][1] + nums[i] xor k
        // f[i][1] = f[i - 1][0] + nums[i] xor k
        // initialize f[0][0] = 0, f[0][1] = -inf. 
        // compress to one dimension dp

        // TC : O(n), SC : O(1)
        int n = nums.size();
        array<long long, 2> f{0, numeric_limits<int>::min() / 2};

        for (int x : nums) {
            long long f0 = f[0];
            f[0] = max(f[0] + x, f[1] + (x ^ k));
            f[1] = max(f[1] + x, f0 + (x ^ k));
        }
        return f[0];
    }
};