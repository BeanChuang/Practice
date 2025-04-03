class Solution {
public:
    int longestWPI(vector<int>& hours) {
        /*** Monotonic Stack ***/
        // 1. find the longest subarray s.t. sum of tiring day - sum of non-tiring day > 0
        //    => hours[i] > 8 seen as 1, hours[i] <= 8 seen as -1
        //    => find the longest subarray s.t. sum of subarray > 0
        //    => use prefix sum to cacl subarray[j..i] by s[i + 1] - s[j], where s [i + 1] = sum of nums[0..i+1)
        // 2. if (1) s[j] < s[j + 1] and s[i] > s[j], then pick s[j] as left will be better 
        //       (2) s[j] > s[j + 1] and s[i] > s[j], then pick s[j] as left will be better 
        //       (3) s[j] > s[j + 1] and s[i] < s[j], then pick s[j + 1] as left will be better  
        //    => we only need to consider j' if j > j' and s[j] > s[j']
        //    => use monotonic decreasing stack to store such j
        // 3. for each s[j], only need to consider the farest i s.t. s[i] > s[j]
        //    => traverse i in reverse order, pop j if s[i] > s[j] because i - 1 is impossible better than i for j
        // TC : O(n), SC : O(n)

        int n = hours.size();
        vector<int> s(n + 1); // s[i + 1] = sum hours[0..i]
        stack<int> st;
        st.push(0); // prefix sum with 0 element
        for (int j = 1; j <= n; j++) {
            s[j] = s[j - 1] + (hours[j - 1] > 8 ? 1 : -1);
            if (s[j] < s[st.top()]) {
                st.push(j);
            }
        }
        int ans = 0;
        for (int i = n; i > 0; i--) {
            while (!st.empty() and s[i] > s[st.top()]) {
                // s[i] > s[j]
                ans = max(ans, i - st.top());
                st.pop();
            }
        }
        return ans;

        /*** Prefix Sum ***/
        // 1. find the longest subarray s.t. sum of tiring day - sum of non-tiring day > 0
        //    => hours[i] > 8 seen as 1, hours[i] <= 8 seen as -1
        //    => find the longest subarray s.t. sum of subarray > 0
        //    => use prefix sum to cacl subarray[j..i] by s[i + 1] - s[j], where s [i + 1] = sum of nums[0..i+1)
        // 2. if s[i] > 0, then longest subarray end at i is i - 0.
        //    if s[i] < 0, then longest subarray end at i is i - pos[s[i] - 1], where pos[k] is the first appear index of k
        // TC : O(n), SC : O(n)

        int n = hours.size(), s = 0, ans = 0;
        vector<int> pos(n + 2);

        for (int i = 1; i <= n; i++) {
            s += hours[i - 1] > 8 ? -1 : 1;
            if (s < 0) {
                ans = i;
            } else {
                if (pos[s + 1]) {
                    ans = max(ans, i - pos[s + 1]);
                }
                if (pos[s] == 0) {
                    pos[s] = i;
                }
            }
        }
        return ans;
    }
};