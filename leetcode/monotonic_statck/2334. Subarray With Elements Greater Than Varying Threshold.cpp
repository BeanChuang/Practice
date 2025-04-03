class Solution {
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        // 1. find any subarray of length k s.t. every element in the subarray > threshold / k
        //    => min element in the subarray must > threshold / k
        // 2. the longer length of subarray, the more possible subarray is valid
        //    => find the longest subarray for each nums[i], where nums[i] is min element in subarray
        //    => use monotonic increasing stack to find nums[l] < nums[i] >= nums[r]
        //    => if min element > threshold / the length subarray, valid subarray found
        // TC : O(n), SC : O(n)

        int n = nums.size();
        stack<int> st;
        st.push(-1); // guard
        for (int r = 0; r <= n; r++) { // i == n : guard
            while (st.size() > 1 and (r == n or nums[r] <= nums[st.top()])) {
                int i = st.top();
                st.pop();
                int len = r - st.top() - 1;
                if (nums[i] > threshold / len) {
                    return len;
                }
            }
            st.push(r);
        }
        return -1;
    }
};
