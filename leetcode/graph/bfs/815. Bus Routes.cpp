class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        // 1. build the bus graph
        // 2. find the shortest path from source bus to destination bus

        // TC : O(N), SC : O(N), where N is sum of all routes length
        int n = routes.size();
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            for (int r : routes[i]) {
                mp[r].push_back(i);
            }
        }

        if (!mp.count(source) || !mp.count(target)) {
            return source != target ? -1 : 0;
        }

        unordered_map<int, int> dis;
        dis[source] = 0;
        queue<int> q;
        q.push(source);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            int dis_x = dis[x];
            for (int bus : mp[x]) {
                for (int y : routes[bus]) {
                    if (!dis.count(y)) {
                        dis[y] = dis_x + 1;
                        q.push(y);
                    }
                }
                routes[bus].clear();
            }
        }
        return dis.count(target) ? dis[target] : -1;
    }
};