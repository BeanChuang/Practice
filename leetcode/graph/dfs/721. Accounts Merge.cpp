class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // 1. convert account name to index, then record all indexes belonging to email
        // 2. dfs these indexes (accounts) of the email and combine the traversed email
        //    to the first index (account)
        // TC : O(LlogM), SC : O(L), where L is sum of all strings length and M is number
        //                                 of strings.

        unordered_map<string, vector<int>> email_to_idx;
        int n = accounts.size();
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                email_to_idx[accounts[i][j]].push_back(i); // add index to email
            }
        }
        
        unordered_set<string> email_set;
        vector<int> vis(n);
        auto dfs = [&](this auto&& dfs, int i) -> void {
            vis[i] = true;
            for (int j = 1; j < accounts[i].size(); j++) {
                string& email = accounts[i][j];
                if (email_set.count(email)) {
                    continue;
                }
                email_set.insert(email);
                for (int k : email_to_idx[email]) {
                    if (!vis[k]) {
                        dfs(k);
                    }
                }
            }
        };

        vector<vector<string>> ans;
        for (int i = 0; i < n; i++) {
            if (vis[i]) {
                continue;
            }

            email_set.clear();
            dfs(i);
            vector<string> res{accounts[i][0]};
            res.insert(res.end(), email_set.begin(), email_set.end());
            ranges::sort(res.begin() + 1, res.end());
            ans.emplace_back(move(res));
        }
        return ans;
    }
};