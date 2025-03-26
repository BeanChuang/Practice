class Solution {
public:
    int kIncreasing(vector<int>& arr, int k) {
        // min operations s.t. arr[i%k] are sorted
        // find the max subsequence
        // TC : O(nlogn), SC : O(n / k)
        int n = arr.size();
        auto min_cnt = [&](int start) -> int {
            vector<int> a;
            for (int i = start; i < n; i += k) {
                auto it = ranges::upper_bound(a, arr[i]);
                if (it == a.end()) {
                    a.push_back(arr[i]);
                } else {
                    *it = arr[i];
                }
            }
            return a.size();
        };

        int ans = n;
        for (int i = 0; i < k; i++) {
            ans -= min_cnt(i);
        }
        return ans;
    }
};
    