class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, 
                    vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        // Note : Each box is contained in one box at most.
        //        All values of containedBoxes[i] are unique.
        //        All values of keys[i] are unique.
        // 1. use bfs to find the box we can open currently
        // 2. record the box we have s.t. we can open it if we get the key.
        // TC : O(n), SC : O(n)
        int ans = 0;
        queue<int> q;
        vector<bool> can_reach(status.size());
        for (int b : initialBoxes) {
            if (status[b] == 1) {
                q.push(b);
            } else {
                can_reach[b] = true;
            }
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            ans += candies[x];
            for (int k : keys[x]) {
                if (status[k] == 0 and can_reach[k]) {
                    q.push(k);
                }
                status[k] = 1;
            }
            for (int b : containedBoxes[x]) {
                if (status[b] == 1) {
                    q.push(b);
                }
                can_reach[b] = true;
            }
        }
        return ans;
    }
};