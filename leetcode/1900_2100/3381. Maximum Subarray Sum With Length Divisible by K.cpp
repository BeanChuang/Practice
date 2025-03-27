class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        // 1. subarray[j, i] divisible by k, then (i - j + 1) % k == 0
        // 2. iterate nums to update nums[i % k] and answer end with i, where j < i
        // TC : O(n), SC : O(k)
        int n = nums.size();
        vector<long long> mod(k, LLONG_MAX / 2);
        mod[k - 1] = 0; // i = -1 = k - 1

        long long sum = 0, ans = LLONG_MIN;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            int j = i % k; 
            ans = max(ans, sum - mod[j]);
            mod[j] = min(mod[j], sum);
        }
        return ans;
    }
};