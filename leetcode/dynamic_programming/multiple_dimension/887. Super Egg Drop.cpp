class Solution {
public:
    int superEggDrop(int k, int n) {
        // f[i][j] : the minimum number of moves that you need to determine with certainty what the value of f is
        //           with (i + 1) floors and j unbroken egg.
        // f[i][k] = min(f[i][k], max(f[i - 1][k - 1], f[i - j][k]) + 1), where 1 <= j <= i.

        vector f(n + 1, vector(k + 1, INT_MAX / 2));
        for (int i = 0; i <= k; i++) {
            f[0][i] = 0; // 0 floors need 0 moves
        }
        
        for (int i = 1; i <= n; i++) {
            f[i][1] = i; // i floor with one egg need i moves
            for (int e = 2; e <= k; e++) {
                // for (int j = 1; j <= i; j++) {
                //     f[i][e] = min(f[i][e], max(f[j - 1][e - 1], f[i - j][e]) + 1);
                // }
                // optimized idea : if j is increasing and eggs num is same
                //                  (1) f[j - 1][e - 1] will be increasing because more floor need more moves
                //                  (2) f[i - j][e] will be decreasing because less floor need less moves
                // we can use binary search to find the min of max(f[j - 1][e - 1], f[i - j][e])
                int left = 1, right = i;
                while (left < right) {
                    int j = left + (right - left) / 2;
                    int inc_term = f[j - 1][e - 1];
                    int dec_term = f[i - j][e];
                    if (inc_term < dec_term) {
                        left = j + 1;
                    } else {
                        right = j;
                    }
                }
                f[i][e] = min(f[i][e], max(f[left - 1][e - 1], f[i - left][e]) + 1);
            }
        }
        return ranges::min(f[n]);
    }
};