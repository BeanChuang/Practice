class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        // f1[i] : max sum end at nums1[i]
        // f2[j] : max sum end at nums2[j]
        // if nums1[i] == nums2[j] => f1[i] = f2[j] = max(f1[i], f2[j]) + nums1[i]
        // if j == m or nums1[i] < nums2[j] => f1[i + 1] = f1[i] + nums1[i]
        // if i == n or nums1[i] > nums2[j] => f2[j + 1] = f2[j] + nums2[j]
        // answer is max(f1[n], f2[m])
        // TC : O(n + m), SC : O(n + m)
        const int MOD = 1'000'000'007;

        int n = nums1.size(), m = nums2.size();
        vector f1(n + 1, 0LL);
        vector f2(m + 1, 0LL);
        int i = 0, j = 0;
        while (i < n or j < m) {
            if (i < n and j < m and nums1[i] == nums2[j]) {
                long long x = max(f1[i], f2[j]) + nums1[i];
                f1[i + 1] = f2[j + 1] = x;
                i++, j++;
            } else if (j == m or (i < n and nums1[i] < nums2[j])) {
                f1[i + 1] = f1[i] + nums1[i];
                i++;
            } else if (i == n or (j < m and nums1[i] > nums2[j])) {
                f2[j + 1] = f2[j] + nums2[j];
                j++;
            }
        }
        return max(f1[n], f2[m]) % MOD;
    }
};
