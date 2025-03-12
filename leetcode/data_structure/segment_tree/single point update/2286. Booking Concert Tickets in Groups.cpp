template<typename T>
class SegmentTree {
    int n;
    vector<T> tree; // sum occupied capacity
    vector<int> mn; // min occupied capacity

    T merge_val(T a, T b) const {
        return a + b;
    }

    void maintain(int node) {
        tree[node] = merge_val(tree[node * 2], tree[node * 2 + 1]);
        mn[node] = min(mn[node * 2], mn[node * 2 + 1]);
    }

    void build(const vector<T>& a, int node, int l, int r) {
        if (l == r) {
            tree[node] = a[l];
            mn[node] = a[l];
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
            mn[node] = val;
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
    SegmentTree(const vector<T>& a) : n(a.size()), tree(4 * n - 1), mn(4 * n - 1) {
        build(a, 1, 0, n - 1);
    }

    void update(int i, T val) {
        update(1, 0, n - 1, i, val);
    }

    // return the leftmost index i in [0, R] s.t. mn[i] <= val otherwise -1
    T find_first(int i, int l, int r, int R, int val) const {
        if (mn[i] > val) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = (l + r) / 2;
        if (mn[i * 2] <= val) {
            return find_first(i * 2, l, m, R, val);
        }
        if (R > m) {
            return find_first(i * 2 + 1, m + 1, r, R, val);
        }
        return -1;
    }

    T query(int ql, int qr) const {
        return query(1, 0, n - 1, ql, qr);
    }

    T get(int i) const {
        return query(1, 0, n - 1, i, i);
    }
};

class BookMyShow {
    // SC : O(n)
    // maintain interval (min occupied capacity, occupied capacity)
    SegmentTree<long long>* tree;
    int n, m;
public:
    BookMyShow(int n, int m) {
        tree = new SegmentTree<long long>(n, 0);
        this->n = n;
        this->m = m;
    }
    
    vector<int> gather(int k, int maxRow) {
        // TC : O(logn)
        // find the concecutive k seats with row number <= max row
        int r = tree->find_first(1, 0, n - 1, maxRow, m - k); // find occupied capacity <= m - k
        if (r < 0) {
            return {};
        }
        int c = tree->get(r);
        tree->update(r, (long long)c + k);
        return {r, c};
    }
    
    bool scatter(int k, int maxRow) {
        // TC : O(logn)
        // find the k seats with row number <= max row
        long long s = tree->query(0, maxRow);
        if (s > (long long) m * (maxRow + 1) - k) {
            return false;
        }
        int i = tree->find_first(1, 0, n - 1, maxRow, m - 1);
        while (k) {
            int x = tree->get(i);
            int left = min(m - x, k);
            tree->update(i, x + left);
            k -= left;
            i++;
        }
        return true;
    }
};
