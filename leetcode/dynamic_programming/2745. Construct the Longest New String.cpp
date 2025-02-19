class Solution {
public:
    int longestString(int x, int y, int z) {
        // "AA" * x, "BB" * y, "AB" * z
        // (1) AA + BB
        // (2) BB + AA, BB + AB
        // (3) AB + AA, AB + AB
        // f[i][j][k][pre] : the longeset length using i * "AA", j * "BB" and 
        //                   k * "AB" end at pre, where pre ∈ [AA, BB, AB]
        // f[i + 1][j][k][0] = max(f[i][j][k][1], f[i][j][k][2]) + 2
        // f[i][j + 1][k][1] = f[i][j][k][0] + 2
        // f[i][j][k + 1][2] = f[i][j][k][1] + 2
        // TC : O(x * y * z), SC : O(x * y * z)

        vector f(x + 2, vector(y + 2, vector<array<bool, 3>>(z + 2, {false, false, false})));
        ranges::fill(f[0][0][0], true);
        
        int ans = 0;
        for (int i = 0; i <= x; i++) {
            for (int j = 0; j <= y; j++) {
                for (int k = 0; k <= z; k++) {
                    f[i + 1][j][k][0] = f[i][j][k][1] or f[i][j][k][2];
                    f[i][j + 1][k][1] = f[i][j][k][0];
                    f[i][j][k + 1][2] = f[i][j][k][1] or f[i][j][k][2];
                    
                    if (f[i + 1][j][k][0] or f[i][j + 1][k][1] or f[i][j][k + 1][2]) {
                        ans = max(ans, (i + j + k) * 2);
                    }
                }
            }
        }
        return ans;
    }
};