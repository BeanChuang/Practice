class Solution {
public:
    int maxSumMinProduct(vector<int>& nums) {
        // 1. min-product is min(arr) * sum(arr)
        // 2. find the max of min-product
        //    - for each min value, the length of array should be as longer as possible.
        //      find (l, r) s.t. nums[l] < nums[i], nums[i] >= nums[r], 
        //      where nums[j] as min and l < i < r
        //    - the max of min-product for nums[i] is sum(l, r) * nums[i]
        //    - use monotonic increasing stack to find l and r
        //    - use prefix sum to calc sum(l, r)
        // TC : O(n), SC : O(n)
        const int MOD = 1'000'000'007;
        int n = nums.size();
        long long ans = 0;
        stack<int> st;
        st.push(-1); // gurad

        vector<long long> s(n + 1); // s[i] is sum of nums[0, i)
        partial_sum(nums.begin(), nums.end(), s.begin() + 1);

        for (int r = 0; r <= n; r++) { // guard for i == n
            while (st.size() > 1 and (r == n or nums[r] <= nums[st.top()])) {
                // nums[i] >= nums[r]
                int i = st.top();
                st.pop();
                int l = st.top(); // nums[l] < nums[i]
                ans = max(ans, (s[r] - s[l + 1]) * nums[i]); 
            }
            st.push(r);
        }
        return static_cast<int>(ans % MOD);
    }
};