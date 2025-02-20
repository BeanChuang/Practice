class Solution {
public:
    long long numberOfWays(string s) {
        // f[i][j] : select i building end at j
        // if s[k] == '1': f[i][1] = f[i - 1][0] + 1
        // if s[k] == '0': f[i][0] = f[i - 1][1] + 1
        array<array<long long, 2>, 4> f{};
        f[0][0] = f[0][1] = 1;
        
        for (char ch : s) {
            for (int i = 1; i <= 3; i++) {
                int d = ch - '0';
                f[i][d] += f[i - 1][1 - d];
            }
        }
        return f[3][0] + f[3][1];

        // int n = s.length();
        // vector memo(n, vector(4, vector(3, -1LL)));
        // auto dfs = [&](this auto&& dfs, int i, int j, int pre) -> long long {
        //     if (j == 0) {
        //         return 1;
        //     }
        //     if (i < 0) {
        //         return 0;
        //     }
        //     long long& res = memo[i][j][pre];
        //     if (res != -1) {
        //         return res;
        //     }
        //     res = dfs(i - 1, j, pre);
        //     if (s[i] - '0' != pre) {
        //         res += dfs(i - 1, j - 1, s[i] - '0');
        //     }
        //     return res;
        // };
        // return dfs(n - 1, 3, 2);
    }
};