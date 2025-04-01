class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        // 1. find the closest left element < arr[i]
        //    find the cloest right element <= arr[i]
        //    => (right[i] - left[i] - 1) subarrays with arr[i] as minimum
        // TC : O(n), SC : O(n)

        const int MOD = 1'000'000'007;
        int n = arr.size();

        // vector<int> left(n, -1), right(n, n);
        // stack<int> st;
        // for (int i = 0; i < n; i++) {
        //     while (!st.empty() and arr[i] <= arr[st.top()]) {
        //         // arr[i] is the first element smaller than or equal to arr[st.top()] on its right
        //         right[st.top()] = i; 
        //         st.pop();
        //     }
        //     if (!st.empty()) {
        //         left[i] = st.top(); // arr[st.top()] is the first element smaller than arr[i] on its left
        //     }
        //     st.push(i);
        // }

        // long long ans = 0;
        // for (int i = 0; i < n; i++) {
        //     ans += (long long) arr[i] * (i - left[i]) * (right[i] - i);
        // }
        // return ans % MOD;

        long long ans = 0;
        stack<int> st;
        st.push(-1); // guard
        for (int r = 0; r <= n; r++) {
            // monotonic increasing
            while (st.size() > 1 and (r == n or arr[r] <= arr[st.top()])) {
                // first element arr[r] <= arr[i], where r > i
                int i = st.top();
                st.pop();
                // first element arr[st.top()] < arr[i], where st.top() < i
                ans += (long long) arr[i] * (i - st.top()) * (r - i);
            }
            st.push(r);
        }
        return ans % MOD;
    }
};