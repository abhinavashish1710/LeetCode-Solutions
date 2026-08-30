class Solution {
public:
    int solve(TreeNode* root, int current) {
        if (root == nullptr)
            return 0;

        current = current * 10 + root->val;

        // Leaf node
        if (root->left == nullptr && root->right == nullptr)
            return current;

        return solve(root->left, current) +
               solve(root->right, current);
    }

    int sumNumbers(TreeNode* root) {
        return solve(root, 0);
    }
};
