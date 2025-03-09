struct node {
    int x, cnt;
    node(int x, int cnt) : x(x), cnt(cnt) {}
};
class SegmentTree {
    vector<node> vp;
    void maintain(int o) {
        node& c = vp[o];
        node& a = vp[o * 2];
        node& b = vp[o * 2 + 1];
        if (a.x == b.x) {
            c.x = a.x;
            c.cnt = a.cnt + b.cnt;
        } else if (a.cnt > b.cnt) {
            c.x = a.x;
            c.cnt = a.cnt - b.cnt;
        } else {
            c.x = b.x;
            c.cnt = b.cnt - a.cnt;
        }
    }

    void build(vector<int>& a, int o, int l, int r) {
        if (l == r) {
            vp[o] = {a[l], 1};
            return;
        }
        int m = (l + r) / 2;
        build(a, o * 2, l, m);
        build(a, o * 2 + 1, m + 1, r);
        maintain(o);
    }
public:
    SegmentTree(vector<int>& a) {
        int n = a.size();
        vp.resize(4 * n, {0, 0});
        build(a, 1, 0, n - 1);
    }
    
    node range_query(int o, int l, int r, int i, int j) {
        if (i > r or j < l) {
            return {0, 0};
        }
        if (i <= l and j >= r) {
            return vp[o];
        }
        int m = (l + r) / 2;
        auto L = range_query(o * 2, l, m, i, j);
        auto R = range_query(o * 2 + 1, m + 1, r, i, j);

        if (L.x == R.x) {
            return node(L.x, L.cnt + R.cnt);
        } else if (L.cnt > R.cnt) {
            return node(L.x, L.cnt - R.cnt);
        } else {
            return node(R.x, R.cnt - L.cnt);
        }
    }
};

class MajorityChecker {
    int n;
    unordered_map<int, vector<int>> bucket; // val -> idx
    SegmentTree* tree;
public:
    // TC : O(nlogn), SC : O(n)
    MajorityChecker(vector<int>& arr) {
        n = arr.size();
        for (int i = 0; i < n; i++) {
            bucket[arr[i]].push_back(i);
        }
        tree = new SegmentTree(arr); 
    }
    
    int query(int left, int right, int threshold) {
        node a = tree->range_query(1, 0, n - 1, left, right);
        auto lb = ranges::lower_bound(bucket[a.x], left);
        auto ub = ranges::upper_bound(bucket[a.x], right);
        return (ub - lb) >= threshold ? a.x : -1;
    }
};
