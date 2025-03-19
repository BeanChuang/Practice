template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    FenwickTree(int n) : tree(n + 1) {}

    // 1 <= i <= n
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] = max(tree[i], val);
        }
    }

    // 1 <= i <= n
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res = max(res, tree[i]);
        }
        return res;
    }
};

class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        // 1. find the max score s.t. all the older one has better score than the younger one.
        // 2. sort by scores, then find the max sum scores with max age ages[i]
        // 3. use dynamic programming => f[i] = max(f[i], f[j] + 1), where f[i] is max score with max age i
        // 4. optimize by using fenwick tree to maintain max sum score with age as index
        // TC : (nlogn + nlogU), SC : O(U), where U is maximum of ages
        int n = scores.size();
        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++) {
            a.emplace_back(scores[i], ages[i]);
        }
        ranges::sort(a);
        int mx_age = ranges::max(ages);
        FenwickTree<int> tree(mx_age);

        for (auto& [score, age] : a) {
            tree.update(age, tree.pre(age) + score);
        }
        return tree.pre(mx_age);
    }
};