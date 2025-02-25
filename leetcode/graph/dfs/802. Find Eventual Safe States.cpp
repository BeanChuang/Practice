class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        // 1. dfs each node.
        //    - it is safe node if each path end at terminal node,
        //      otherwise it is not a safe node.
        // TC : O(n), SC : O(n + m), where m is length of edges
        int n = graph.size();
        vector<int> status(n);

        auto dfs = [&](this auto&& dfs, int x) -> bool {
            status[x] = 1;
            for (int y : graph[x]) {
                if (status[y] == 1 or (status[y] == 0 and !dfs(y))) {
                    return false;
                }
            }
            status[x] = 2;
            return true;
        };

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (status[i] == 2 or (status[i] == 0 and dfs(i))) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};