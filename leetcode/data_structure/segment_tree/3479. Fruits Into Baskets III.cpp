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

    T get(int i) const {
        return query(1, 0, n - 1, i, i);
    }

    T find_first(int node, int l, int r, int val) {
        if (tree[node] < val) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = (l + r) / 2;
        int i = find_first(node * 2, l, m, val);
        if (i == -1) {
            i = find_first(node * 2 + 1, m + 1, r, val);
        }
        return i;
    }
};
class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = baskets.size(), ans = 0;
        
        SegmentTree<int> tree(baskets);
        for (int x : fruits) {
            int idx = tree.find_first(1, 0, n - 1, x);
            if (idx == -1) {
                ans++;
            } else {
                tree.update(idx, -1);
            }
        }
        return ans;
    }
};