class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        // 1. find the number subarrays include nums[i] as maximum/minimum,
        //    then add/subtract cnt[i] * nums[i]
        // 2. use monotonic stack to find out.
        // TC : O(n), SC : O(n)
        int n = nums.size();
        auto find_max = [&]() -> long long {
            stack<int> st;
            long long res = 0;
            st.push(-1);
            for (int r = 0; r <= n; r++) {
                while (st.size() > 1 and (r == n or nums[r] >= nums[st.top()])) {
                    int i = st.top();
                    st.pop();
                    int l = st.top();
                    res += (long long)(r - i) * (i - l) * nums[i]; // nums[i] is maximum of nums(l, r)
                }
                st.push(r);
            }
            return res;
        };

        long long ans = find_max();
        for (int& x : nums) {
            x = -x;
        }
        return ans + find_max();
    }
};