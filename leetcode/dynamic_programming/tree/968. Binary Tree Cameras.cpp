class Solution {
public:
    int minCameraCover(TreeNode* root) {
        // x -> by fa, y -> by self, z -> by child
        // x = min(left_y, left_z) + min(right_y, right_z)
        // y = min(left_x, left_y, left_z) + min(right_x, right_y, right_z) + 1
        // z = min(left_y + right_z, left_z + right_y, left_y + right_y)
        // edge case x = 0, y = inf, z = 0
        // TC : O(n), SC : O(n)
        
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> array<int, 3> {
            if (!root) {
                return {0, INT_MAX / 2, 0};
            }
            int by_fa, by_self, by_child;
            auto [l_by_fa, l_by_self, l_by_child] = dfs(root->left);
            auto [r_by_fa, r_by_self, r_by_child] = dfs(root->right);

            by_fa = min(l_by_self, l_by_child) + min(r_by_self, r_by_child);
            by_self = min({l_by_fa, l_by_self, l_by_child}) +
                      min({r_by_fa, r_by_self, r_by_child}) + 1;
            by_child = min({l_by_self + r_by_child, l_by_child + r_by_self, l_by_self + r_by_self});
            return {by_fa, by_self, by_child};
        };

        auto [_, by_self, by_child] = dfs(root);
        return min(by_self, by_child);
    }
};