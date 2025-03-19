template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    FenwickTree(int n) : tree(n + 1) {}

    // 1 <= i <= n
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 1 <= i <= n
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }

    // 1 <= i <= n
    T query(int l, int r) const {
        if (r < l) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }
};

class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        // move queried point to head by create 2 * m array
        // use fenwick tree for dynamic update and query
        // TC : O(m + nlogm), SC : O(m)
        int n = queries.size();
        FenwickTree<int> tree(2 * m);
        vector<int> idx(m + 1);
        
        for (int i = 1; i <= m; i++) {
            tree.update(i + m, 1);
            idx[i] = i + m;
        }


        vector<int> ans(n);
        for (int i = 0, j = m; i < n; i++, j--) {
            int x = queries[i];
            ans[i] = tree.pre(idx[x] - 1);
            tree.update(idx[x], -1);
            tree.update(j, 1);
            idx[x] = j;
        }
        return ans;
    }
};