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
    vector<int> resultArray(vector<int>& nums) {
        // count the number of element greater than x
        // use fenwick tree to count number of element in [x + 1, mx]
        // TC : O(nlogm), SC : O(m)
        auto sorted = nums;
        ranges::sort(sorted);
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        int m = sorted.size();

        vector<int> a{nums[0]}, b{nums[1]};
        FenwickTree<int> tree1(m + 1), tree2(m + 1);
        tree1.update(ranges::lower_bound(sorted, nums[0]) - sorted.begin() + 1, 1);
        tree2.update(ranges::lower_bound(sorted, nums[1]) - sorted.begin() + 1, 1);
        for (int i = 2; i < nums.size(); i++) {
            int x = nums[i];
            int v = ranges::lower_bound(sorted, x) - sorted.begin() + 1;
            int gc1 = tree1.query(v + 1, m);
            int gc2 = tree2.query(v + 1, m);
            if (gc1 > gc2 or (gc1 == gc2 and a.size() <= b.size())) {
                a.push_back(x);
                tree1.update(v, 1);
            } else {
                b.push_back(x);
                tree2.update(v, 1);
            }
        }
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }
};