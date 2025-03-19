template<typename T>
class FenwickTree {
    vector<T> tree;
public:
    FenwickTree(int n) : tree(n + 1) {}

    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    T pre(int i) {
        T res = 0;
        for (; i > 0; i &= (i - 1)) {
            res += tree[i];
        }
        return res;
    }

    T query(int l, int r) {
        if (l > r) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }
};

class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        // 1. find the count of elements 
        //    - strictly less than x (presum[x] - presum[0])
        //    - strictly greater than x (presum[U] - presum[x]), where U is maximum of all instructions
        // 2. need dynamic update
        //    => use fenwick tree to support (1) in O(logU) and (2) in O(logU)
        // TC : O(nlogU), SC : O(U), where U is maximum element
        const int MOD = 1'000'000'007;
        int n = instructions.size();
        auto sorted = instructions;
        ranges::sort(sorted);
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        int mx = sorted.size();

        FenwickTree<int> tree(mx + 1);

        long ans = 0;
        for (int x : instructions) {
            int i = ranges::lower_bound(sorted, x) - sorted.begin() + 1;
            ans += min(tree.query(1, i - 1), tree.query(i + 1, mx));
            tree.update(i, 1);
        }
        return ans % MOD;
    }
};