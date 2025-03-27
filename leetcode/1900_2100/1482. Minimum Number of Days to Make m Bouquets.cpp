class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        // 1. use binary search to find min day
        // TC : O(nlogn), SC : O(1)

        int n = bloomDay.size();
        if ((long long)m * k > n) {
            return -1;
        }


        auto check = [&](int day) -> bool {
            int res = 0, cnt = 0;
            for (int x : bloomDay) {
                if (day >= x) {
                    cnt++;
                } else {
                    cnt = 0;
                }
                
                if (cnt == k) {
                    res++;
                    cnt = 0;
                }
            }
            return res >= m;
        };

        int l = ranges::min(bloomDay), r = ranges::max(bloomDay);
        while (l < r) {
            int d = (l + r) / 2;
            if (!check(d)) {
                l = d + 1;
            } else {
                r = d;
            }
        }
        return l;
    }
};