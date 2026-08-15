class Solution {
public:
    int height(TreeNode* root) {
        if (!root) return 0;

        int l = height(root->left);
        if (l == -1) return -1;

        int r = height(root->right);
        if (r == -1) return -1;

        if (abs(l - r) > 1) return -1;

        return 1 + max(l, r);
    }

    bool isBalanced(TreeNode* root) {
        return height(root) != -1;
    }
};
