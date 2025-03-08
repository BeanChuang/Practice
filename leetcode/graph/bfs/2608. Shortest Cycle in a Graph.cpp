class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        // 1. bfs each node is not visited
        // 2. update answer if we tarverse the same node again
        //    ans = min(ans, dis[i, j] + dis[i, k] + dis[j, k])
        // TC : O(nm), SC : O(n + m), where m is edges length

        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        vector<int> dis(n, -1);
        auto bfs = [&](int i) -> int {
            ranges::fill(dis, -1);
            queue<pair<int, int>> q;
            q.emplace(i, -1);
            dis[i] = 0;
            int res = INT_MAX;
            while (!q.empty()) {
                auto [x, fa] = q.front();
                q.pop();
                for (int y : g[x]) {
                    if (dis[y] < 0) {
                        dis[y] = dis[x] + 1;
                        q.emplace(y, x);
                    } else if (y != fa) {
                        res = min(res, dis[x] + dis[y] + 1);
                    }
                }
            }
            return res;
        };
        
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            ans = min(ans, bfs(i));
        }
        return ans == INT_MAX ? -1 : ans;
    }
};