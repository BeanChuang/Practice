class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        // 1. for each nums[i], find left cloest index s.t. nums[left[i]] < nums[i]
        //                      find right cloest index s.t. nums[right[i]] < nums[i]
        // TC : O(n), SC : O(n)
        int n = nums.size();
        vector<int> left(n, -1);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() and nums[i] <= nums[st.top()]) {
                st.pop();
            }
            if (!st.empty()) {
                left[i] = st.top();
            }
            st.push(i);
        }
        
        st = stack<int>();
        vector<int> right(n, n);
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() and nums[i] <= nums[st.top()]) {
                st.pop();
            }
            if (!st.empty()) {
                right[i] = st.top();
            }
            st.push(i);
        }

        int ans = nums[k];
        for (int i = 0; i < n; i++) {
            int l = left[i], r = right[i]; 
            if (l < k and k < r) { // (l, r) is exclusive
                ans = max(ans, nums[i] * (r - l - 1));
            }
        }
        return ans;
    }
};