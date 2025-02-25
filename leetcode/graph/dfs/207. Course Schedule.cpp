class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 1. build the graph based on prerequisites
        // 2. record status of each course, 
        //    where 0 is not traversed
        //          1 is traversing
        //          2 is has been traversed
        // TC : O(V + E), SC : O(V + E)
        
        vector<vector<int>> g(numCourses);
        for (auto& p : prerequisites) {
            int a = p[0], b = p[1];
            g[b].push_back(a);
        }
        
        vector<int> status(numCourses);
        auto dfs = [&](this auto&& dfs, int x) -> bool {
            status[x] = 1;
            for (int y : g[x]) {
                if (status[y] == 1 or (status[y] == 0 and !dfs(y))) {
                    return false;
                }
            }
            status[x] = 2;
            return true;
        };
        for (int i = 0; i < numCourses; i++) {
            if (status[i] == 0 and !dfs(i)) {
                return false;
            }
        }
        return true;
    }
};