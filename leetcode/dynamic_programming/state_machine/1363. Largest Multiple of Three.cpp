class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        // 1. find the longest length of subset of digits s.t. its sum module three equal to zero
        // 2. reconstruct subset by dp status.
        // 3. sort the subset in decreasing order and concatenate them.
        
        int n = digits.size();
        vector<array<int, 3>> f(n + 1, {0, INT_MIN, INT_MIN});
        ranges::sort(digits); // find the maximum combination from end to start

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                int k = (j - digits[i] % 3 + 3) % 3;
                f[i + 1][j] = max(f[i][j], f[i][k] + 1);
            }
        }
        
        if (f[n][0] == 0) {
            return "";
        }

        int d = 0;
        string ans;
        for (int i = n - 1; i >= 0; i--) {
            int k = (d - digits[i] % 3 + 3) % 3;
            if (f[i + 1][d] == f[i][k] + 1) {
                ans.push_back('0' + digits[i]);
                d = k;
            }
        }
        return ans[0] == '0' ? "0" : ans;
    }
};