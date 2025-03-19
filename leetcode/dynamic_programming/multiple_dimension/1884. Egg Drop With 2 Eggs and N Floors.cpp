class Solution {
    public:
        int twoEggDrop(int n) {
            // f[i] : min moves that you need to determine with certainty what the value of f is.
            // idea : dropping egg at each floor, then find the min moves of them.
            //        For each floor, we should find the max moves of both conditions.
            //        Assume drop egg at j floor :
            //        (1) broken : f[i] = j (in wrose case we need drop j times) 
            //        (2) not broken : f[i] = f[i - j] (equal to f[i - j] times => sub-problem)
            //        => f[i] = min(f[i], max(j, f[i - j] + 1)), where 1 <= j <= i
            vector f(n + 1, INT_MAX / 2);
            f[0] = 0;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= i; j++) {
                    f[i] = min(f[i], max(j, f[i - j] + 1));
                }
            }
            return f[n];
        }
    };
    