class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        // // (1) use hashmap to maintain window max diff <= 2
        // // TC : O(n), SC : O(1)
        // long long ans = 0;
        // map<int, int> cnt; // at most 3 elements
        // for (int l = 0, r = 0; r < nums.size(); r++) {
        //     cnt[nums[r]]++;
        //     while (rbegin(cnt)->first - begin(cnt)->first > 2) {
        //         if (--cnt[nums[l]] == 0) {
        //             cnt.erase(nums[l]);
        //         }
        //         l++;
        //     }
        //     ans += r - l + 1;
        // }
        // return ans;


        // (2) use monotonic decreasing/increasing deque to maintain max/min
        // TC : O(n), SC : O(n)
        deque<int> max_dq, min_dq;
        int n = nums.size();
        long long ans = 0;
        for (int l = 0, r = 0; r < n; r++) {
            while (!max_dq.empty() and nums[max_dq.back()] < nums[r]) {
                max_dq.pop_back();
            }
            while (!min_dq.empty() and nums[min_dq.back()] > nums[r]) {
                min_dq.pop_back();
            }
            max_dq.push_back(r);
            min_dq.push_back(r);

            while (nums[max_dq.front()] - nums[min_dq.front()] > 2) {
                if (max_dq.front() <= l) {
                    max_dq.pop_front();
                }
                if (min_dq.front() <= l) {
                    min_dq.pop_front();
                }
                l++;
            }
            ans += r - l + 1;
        }
        return ans;
    }
};