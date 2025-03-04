
#include <ranges>
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        // group meeting by their time
        // start from node knows the secret

        // TC : O(mlogm), SC : O(n + m)
        
        int m = meetings.size();
        ranges::sort(meetings, less<>{}, [](auto& meet) { return meet[2]; });

        vector<bool> secret(n);
        secret[0] = secret[firstPerson] = true;
        for (int i = 0; i < m;) {
            int cur_time = meetings[i][2];
            unordered_map<int, vector<int>> g;
            for (; i < m and cur_time == meetings[i][2]; i++) {
                int u = meetings[i][0], v = meetings[i][1];
                g[u].push_back(v);
                g[v].push_back(u);
            }
            
            unordered_map<int, bool> vis;
            auto dfs = [&](this auto&& dfs, int x) -> void {
                vis[x] = true;
                secret[x] = true;
                for (int y : g[x]) {
                    if (!vis[y]) {
                        dfs(y);
                    }
                }
            };

            for (auto [i, _] : g) {
                if (secret[i]) {
                    dfs(i);
                }
            }
        }

        vector<int> ans;
        for (int i : views::iota(0, n) | views::filter([&secret](int i) { return secret[i]; })) {
            ans.push_back(i);
        }
        return ans;
    }
};