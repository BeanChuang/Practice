class Solution {
public:
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        // f[i][j] : the max money can eran after cutting (i + 1) * (j + 1) piece of wood 
        vector f(m, vector(n, 0LL));
        for (auto& price : prices) {
            int h = price[0], w = price[1], p = price[2];
            f[h - 1][w - 1] = p;
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int cut_h = 0; cut_h < (i + 1) / 2; cut_h++) {
                    f[i][j] = max(f[i][j], f[cut_h][j] + f[i - (cut_h + 1)][j]);
                }
                for (int cut_v = 0; cut_v < (j + 1) / 2; cut_v++) {
                    f[i][j] = max(f[i][j], f[i][cut_v] + f[i][j - (cut_v + 1)]);
                }
            }
        }
        return f[m - 1][n - 1];
    }
};