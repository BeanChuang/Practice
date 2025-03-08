class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        // find the min time s.t. the sent msg return back to each data server.
        // assume min distance from data server[i] to master is d
        //        patience[i] is t
        // then, last msg sent at (int) ((2 * d - 1) / t) * t
        //       last msg received need 2 * d
        //       after last msg done need 1 
        // total = ((2 * d - 1) / t) * t + 2 * d + 1
        // TC : O(n + E), SC : O(n, E), where E is length of edges
        
        int n = patience.size();
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }       
        
        queue<int> q;
        vector<int> dis(n, INT_MAX);
        dis[0] = 0;
        q.push(0);

        int idle_time = 1;
        while (!q.empty()) {
            int x = q.front();
            if (x != 0) {
                int d = dis[x], t = patience[x];
                idle_time = max(idle_time, (d * 2 - 1) / t * t + 2 * d + 1);
            }
            q.pop();
            for (int y : g[x]) {
                if (dis[y] > dis[x] + 1) {
                    dis[y] = dis[x] + 1;
                    q.push(y);
                }
            }
        }
        return idle_time;
    }
};