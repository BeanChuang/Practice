const int MX = 100001;
int prime_score[MX];
int init = [] {
    for (int i = 2; i < MX; i++) {
        if (prime_score[i] == 0) {
            for (int j = i; j < MX; j += i) {
                prime_score[j]++;
            }
        }
    }
    return 0;
}();

class Solution {
    const int MOD = 1'000'000'007;
    long long qpow(long long x, int n) {
        long long res = 1;
        for (; n; n /= 2) {
            if (n % 2) {
                res = res * x % MOD;
            }
            x = x * x % MOD;
        }
        return res;
    }
public:
    int maximumScore(vector<int>& nums, int k) {
        // 1. cacl prime score array
        // 2. count the number of subarray with nums[i] as maximum
        //    - use monotonic decreasing stack to count.
        //      (1) find the closest left nums[l] >= nums[i] (smalest index first) and 
        //          the closest right nums[r] > nums[i] (avoid duplicate cases)
        //          => count of such subarrays is (i - l) * (r - i)
        // 3. Greedy to select the max score first.
        //    (1) sort idx array by nums[idx]
        // 4. multiply score until k operations done.
        // TC : O(nlogn + nlogMX), SC : O(n + MX)
        int n = nums.size();
        
        vector<int> left(n, -1), right(n, n);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            while (!st.empty() and prime_score[x] > prime_score[nums[st.top()]]) {
                right[st.top()] = i;
                st.pop();
            }
            if (!st.empty()) {
                left[i] = st.top();
            }
            st.push(i);
        }
        
        vector<int> idx(n);
        ranges::iota(idx, 0);
        ranges::sort(idx, greater<int>{}, [&](int i) { return nums[i]; } );
        
        long long ans = 1;
        for (int i : idx) {
            long long cnt = (long long) (i - left[i]) * (right[i] - i);
            if (k <= cnt) {
                ans = ans * qpow(nums[i], k) % MOD;
                break;
            } 
            ans = ans * qpow(nums[i], cnt) % MOD;
            k -= cnt;
        }
        return ans;
    }
};