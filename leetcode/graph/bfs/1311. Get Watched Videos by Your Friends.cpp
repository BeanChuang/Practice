class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        // find the frequency of watchedVideos with shoretest distance equal to `level`
        // TC : O(nlogn + m), SC : O(n)
        
        vector<int> q;
        q.push_back(id);
        vector<bool> vis(friends.size());
        vis[id] = true;
        while (level-- and !q.empty()) {
            vector<int> next;
            for (int x : q) {
                for (int y : friends[x]) {
                    if (!vis[y]) {
                        vis[y] = true;
                        next.push_back(y);
                    }
                }
            }
            q = std::move(next);
        }
        
        unordered_map<string, int> cnt;
        for (int i : q) {
            if (i != id) {
                for (string& video : watchedVideos[i]) {
                    cnt[video]++;
                }
            }
        }
        
        vector<string> ans;
        for (auto [video, _] : cnt) {
            ans.push_back(video);
        }
        ranges::sort(ans, [&cnt](string& s, string& t) { 
            return cnt[s] == cnt[t] ? s < t : cnt[s] < cnt[t];
        });
        return ans;
    }
};