template<typename T>
class SegmentTree {
    int n;
    vector<T> tree;

    T merge_val(T a, T b) const {
        return max(a, b);
    }

    void maintain(int node) {
        tree[node] = merge_val(tree[node * 2], tree[node * 2 + 1]);
    }

    void build(const vector<T>& a, int node, int l, int r) {
        if (l == r) {
            tree[node] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, node * 2, l, m);
        build(a, node * 2 + 1, m + 1, r);
        maintain(node);
    }

    // update node as val
    void update(int node, int l, int r, int i, T val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) {
            update(node * 2, l, m, i, val);
        } else {
            update(node * 2 + 1, m + 1, r, i, val);
        }
        maintain(node);
    }

    // query [ql, qr] in [l, r]
    T query(int node, int l, int r, T ql, T qr) const {
        if (ql <= l and r <= qr) {
            return tree[node];
        }
        int m = (l + r) / 2;
        if (qr <= m) {
            return query(node * 2, l, m, ql, qr);
        }
        if (ql > m) {
            return query(node * 2 + 1, m + 1, r, ql, qr);
        }
        T l_res = query(node * 2, l, m, ql, qr);
        T r_res = query(node * 2 + 1, m + 1, r, ql, qr);
        return merge_val(l_res, r_res);
    }

public:
    SegmentTree(int n, T init_val) : SegmentTree(vector<T>(n, init_val)) {}
    SegmentTree(const vector<T>& a) : n(a.size()), tree(4 * n - 1) {
        build(a, 1, 0, n - 1);
    }

    void update(int i, T val) {
        update(1, 0, n - 1, i, val);
    }

    T query(int ql, int qr) const {
        return query(1, 0, n - 1, ql, qr);
    }

    T query_by_right(int node, int l, int r, int R) const {
        if (R >= r) {
            return tree[node];
        }
        int m = (l + r) / 2;
        if (R <= m) {
            return query_by_right(node * 2, l, m, R);
        }
        return max(tree[node * 2], query_by_right(node * 2 + 1, m + 1, r, R));
    }

    T get(int i) const {
        return query(1, 0, n - 1, i, i);
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        // segment tree maintain max consecutive length in region
        // if obstacle at 7, then it would generate available region with length 7
        // if obstable at 2, then it would generate available region with length 2, and 7 -> (7 - 2)
        // for queried range [0, x], it can be divided into two parts, assume x = 8 => [0, 8]
        // (1) complete : (0, 2), (2, 7)
        // (2) non complete : (7, 8)
        // => if right endpoint in [0, x], then it is complete
        // => we can save the length at its right endpoint as d[i]
        // d[i] = 0 if there is no obstable at i otherwise the distance from leftmost obstable to rightmost obstable
        // TC : O(U + qlogU), where U is maximum of all x, SC : O(U)
        int m = 0;
        for (auto& q : queries) {
            m = max(m, q[1] + 1);
        }
        
        set<int> st{0, m};
        SegmentTree<int> tree(m, 0);

        vector<bool> ans;
        for (auto& q : queries) {
            int x = q[1];
            auto it = st.lower_bound(x);
            int pre = *prev(it); // the leftmost obstable of x
            if (q[0] == 1) {
                int nxt = *it;
                st.insert(x);
                tree.update(x, x - pre);
                tree.update(nxt, nxt - x);
            } else {
                int max_region = max(tree.query_by_right(1, 0, m - 1, pre), x - pre);
                ans.push_back(max_region >= q[2]);
            }
        }
        return ans;
    }
};