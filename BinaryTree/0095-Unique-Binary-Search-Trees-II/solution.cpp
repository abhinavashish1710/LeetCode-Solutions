class Solution {
    vector<TreeNode*> build(int l, int r) {
        if (l > r)
            return {nullptr};

        vector<TreeNode*> ans;

        for (int root = l; root <= r; root++) {
            vector<TreeNode*> left = build(l, root - 1);
            vector<TreeNode*> right = build(root + 1, r);

            for (auto L : left) {
                for (auto R : right) {
                    TreeNode* node = new TreeNode(root);
                    node->left = L;
                    node->right = R;
                    ans.push_back(node);
                }
            }
        }

        return ans;
    }

public:
    vector<TreeNode*> generateTrees(int n) {
        return build(1, n);
    }
};
