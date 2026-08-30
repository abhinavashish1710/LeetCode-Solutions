class Solution {
public:
    int ans = INT_MIN;

    int solve(TreeNode* root) {
        if (root == nullptr)
            return 0;

        // Ignore negative contributions
        int left = max(0, solve(root->left));
        int right = max(0, solve(root->right));

        // Best path passing through the current node
        int current = root->val + left + right;

        ans = max(ans, current);

        // Return the best single-side path to the parent
        return root->val + max(left, right);
    }

    int maxPathSum(TreeNode* root) {
        solve(root);
        return ans;
    }
};
