class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        // 1. i < j < k, find pattern nums[i] < nums[k] < nums[j]
        // 1. enumearte i and update best (j, k) pair:
        //    - use decreasing stack to traverse in reverse order
        // TC : O(n), SC : O(n)
        
        int n = nums.size(), k = INT_MIN;
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            // prev found (j, k) s.t. nums[k] > nums[i]
            if (nums[i] < k) {
                return true;
            }
            while (!st.empty() and nums[i] > nums[st.top()]) {
                // pair(j, k) found -> (i, st.top())
                k = max(k, nums[st.top()]);
                st.pop();
            }
            st.push(i);
        }
        return false;
    }
};