class Solution {
    public:
        int maximumLength(vector<int>& nums, int k) {
            // 1. find the maximum subsequence s.t. at most k indices i in the
            //    range [0, seq.length - 2] and seq[i] != seq[i + 1]
    
            // f[i][x] : the maximum subsequence length end at x and
            //           at most i non-equal pairs.
            // f[i][x] = max(f[i][x] + 1, f[i - 1][y] + 1), 
            //          where x != y and index of y should be < x
            // => time complexity will be O(n^2 * k)
            // => we can keep pre[k] as maximum subsequence s.t. at most k invalid
            //    indices.
            // => then, the complexity can be optimized as O(n * k)
            
            int n = nums.size();
            vector f(k + 1, unordered_map<int, int>{});
            vector pre(k + 1, 0);
    
            for (int x : nums) {
                // note : i should be start from k to 0 because pre will be used
                //        from pre[i - 1]
                for (int i = k; i >= 0; i--) {
                    f[i][x] = f[i][x] + 1;
                    if (i > 0) {
                        f[i][x] = max(f[i][x], pre[i - 1] + 1);
                    } 
                    pre[i] = max(pre[i], f[i][x]);
                }
            }
            return pre[k];
        }
    };