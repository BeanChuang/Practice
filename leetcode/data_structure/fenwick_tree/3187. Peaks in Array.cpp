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
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        // 1. query count of peaks in range [l, r] = cnt[r] - cnt[l - 1], except boundary 0, n - 1
        // 2. support update single point
        // => use fenwick tree to calculate presum and support dynamic update
        // TC : O((n + q)logn), where q is length of queries, SC : O(n)
        int n = nums.size();
        FenwickTree<int> tree(n);
        
        for (int i = 1; i < n - 1; i++) {
            if (nums[i] > max(nums[i - 1], nums[i + 1])) {
                tree.update(i + 1, 1);
            }
        }

        auto update = [&](int i, int delta) {
            if (nums[i] > max(nums[i - 1], nums[i + 1])) {
                tree.update(i + 1, delta);
            }
        };
        
        vector<int> ans;
        for (auto& q : queries) {
            if (q[0] == 1) {
                int l = q[1], r = q[2];
                ans.push_back(tree.query(l + 2, r)); // (l + 1, r + 1) => [l + 2, r]
            } else if (q[0] == 2) {
                int index = q[1], val = q[2];
                for (int i = max(1, index - 1); i <= min(n - 2, index + 1); i++) {
                    update(i, -1);
                }
                nums[index] = val;
                for (int i = max(1, index - 1); i <= min(n - 2, index + 1); i++) {
                    update(i, 1);
                }
            }
        }
        return ans;
    }
};