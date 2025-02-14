class Solution {
public:
    long long countSubstrings(string s) {
        // idea : use remainder to check it can be divisible
        // (val * 10 + d) % d = ((val % d) * 10 + d) % d
        // f[i][m][r] : first 'i' digits module by 'm' with remainder 'r'
        // f[i][m][((r * 10) + d) % d] += f[i - 1][m][r] 
        // Note : i can be compressed
        
        int n = s.length();
        long long ans = 0;
        array<int, 9> f[10]{}; // 0 <= mod < 10, 0 < remainder < mod
        
        for (char d : s) {
            d -= '0';
            for (int m = 1; m < 10; m++) {
                array<int, 9> new_f{};
                // Note : d be a new substring
                new_f[d % m] = 1;
                for (int r = 0; r < m; r++) {
                    // update the count of substrings end at current digit mod by m
                    new_f[((r * 10) + d) % m] += f[m][r];
                }
                f[m] = move(new_f);
            }
            ans += f[d][0]; // add the substring which remainder is zero mod by d
        }
        return ans;
    }
};