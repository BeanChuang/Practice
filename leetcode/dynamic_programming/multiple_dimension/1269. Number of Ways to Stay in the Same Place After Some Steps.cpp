class Solution {
public:
    int numWays(int steps, int arrLen) {
        // define f[i][j] : number ways with i steps at pos j
        // it is impossible to move back origin if j > steps / 2
        // => the max pos is min(steps / 2 + 1, arrLen)
        // initialize f[0][0] = 1
        // f[i][j] = f[i - 1][j] + // stay
        //           f[i - 1][j - 1] + // move left
        //           f[i - 1][j + 1]   // move right
        // Note : negative position `j` is invalid. 
        // TC : O(steps * min(steps, arrLen)), SC : O(min(steps, arrLen))
        
        const int MOD = 1'000'000'007;
        int n = min(steps / 2 + 1, arrLen);
        vector f(n, 0);
        f[0] = 1;

        for (int i = 1; i <= steps; i++) {
            vector new_f(n, 0);
            for (int j = 0; j <= min(i, n - 1); j++) {
                new_f[j] = f[j];
                if (j > 0) {
                    new_f[j] = (new_f[j] + f[j - 1]) % MOD;
                }
                if (j < n - 1) {
                    new_f[j] = (new_f[j] + f[j + 1]) % MOD;
                }
            }
            swap(new_f, f);
        }
        return f[0];
    }
};