class Solution {
public:
    int maximizeWin(vector<int>& pos, int k) {
        // f[i] : maximum prize with one segment in pos[0:i]
        // f[i] = max(f[i - 1], i - j + 1), where j is the min index s.t. pos[i] - pos[j] < k
        // ans = max(ans, f[j] + i - j + 1) 
        // use binary search to find the index j in O(logn)
        // optimize : use sliding window instead of binary search in O(1)
        // TC : O(n), SC : O(n)

        int n = pos.size();
        int ans = 0;
        vector f(n + 1, 0);
        for (int l = 0, r = 0; r < n; r++) {
            // note : l and r are 0-index, but f is 1-index
            while (pos[r] - pos[l] > k) {
                l++;
            }
            f[r + 1] = max(f[r], r - l + 1);
            ans = max(ans, f[l] + r - l + 1);
        }
        return ans;
    }
};