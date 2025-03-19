class Solution {
public:
    int amountOfTime(TreeNode* root, int start) {
        // 1. find the longest path from start node to leaf node
        // case1 : start node as root => find the max depth
        // case2 : start node as leaf => find the max depth include start node in left or right subtree
        // TC : O(n), SC : O(n)
        int ans = 0;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> pair<TreeNode*, int> {
            if (!node) {
                return {nullptr, 0};
            }
            auto [l_node, l_depth] = dfs(node->left);
            auto [r_node, r_depth] = dfs(node->right);
            
            // case 1
            if (node->val == start) {
                ans = max(l_depth, r_depth); 
                return {node, 1};
            }

            // case 2
            if (l_node or r_node) {
                ans = max(ans, l_depth + r_depth);
                return l_node ? make_pair(l_node, l_depth + 1) : make_pair(r_node, r_depth + 1);
            }
            return {nullptr, max(l_depth, r_depth) + 1};
        };

        dfs(root);
        return ans;
    }
};