class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        // minimize the maximum balls in bag after operations
        // TC : O(nlogU), SC : O(1), where U is max of nums

        auto check = [&](int k) -> bool {
            long long cnt = 0;
            for (int x : nums) {
                // cnt += (x + k - 1) / k - 1;
                cnt += (x - 1) / k;
                if (cnt > maxOperations) {
                    return false;
                }
            }
            return true;
        };

        int l = 1, r = ranges::max(nums);
        while (l < r) {
            int m = l + (r - l) / 2;
            if (!check(m)) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return l;
    }
};
        