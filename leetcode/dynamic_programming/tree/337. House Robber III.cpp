class Solution {
public:
    int rob(TreeNode* root) {
        // dfs(root) : max amount of money the thief can rob
        // each node has (rob, not rob status)
        // TC : O(n), SC : O(n)

        auto dfs = [&](this auto&& dfs, TreeNode* node) -> array<int, 2> {
            if (!node) {
                return {0, 0};
            }
            auto [l_rob, l_not_rob] = dfs(node->left);
            auto [r_rob, r_not_rob] = dfs(node->right);

            int rob = node->val + l_not_rob + r_not_rob;
            int not_rob = max(l_rob, l_not_rob) + max(r_rob, r_not_rob);
            return {rob, not_rob};
        };
        return ranges::max(dfs(root));
    }
};