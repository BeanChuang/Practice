class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        // 1. f[i][c] : min swap s.t. both nums1[:i] and nums2[:i] are increasing.
        //                            c = true means nums1[i] swap with nums2[i]
        // 2. swapped or not swapped
        //    if (nums1[i] > nums1[i - 1] and nums2[i] > nums2[i - 1])
        //    => f[i][1] = f[i - 1][1] + 1 // swapped
        //    => f[i][0] = f[i - 1][0] // not swapped
        //    if (nums2[i] > nums1[i - 1] and nums1[i] > nums2[i - 1]) 
        //    => f[i][1] = f[i - 1][0] + 1 // swapped
        //    => f[i][0] = f[i - 1][1] // not swapped
        // 3. answer is min(f[n][0], f[n][1])
        // TC : O(n), SC : O(1)
        
        array<int, 2> f{0, 1};

        int n = nums1.size();
        for (int i = 1; i < n; i++) {
            array<int, 2> new_f{INT_MAX, INT_MAX};
            if (nums1[i] > nums1[i - 1] and nums2[i] > nums2[i - 1]) {
                new_f[1] = f[1] + 1;
                new_f[0] = f[0];
            }
            if (nums1[i] > nums2[i - 1] and nums2[i] > nums1[i - 1])  {
                new_f[1] = min(new_f[1], f[0] + 1);
                new_f[0] = min(new_f[0], f[1]);
            }
            swap(f, new_f);
        }
        return min(f[0], f[1]);
    }
};