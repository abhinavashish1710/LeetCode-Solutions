class Solution {
public:
    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int& i, int l, int r) {
        if (l > r) return nullptr;

        TreeNode* root = new TreeNode(preorder[i++]);

        int mid = find(inorder.begin() + l, inorder.begin() + r + 1, root->val) - inorder.begin();

        root->left = build(preorder, inorder, i, l, mid - 1);
        root->right = build(preorder, inorder, i, mid + 1, r);

        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int i = 0;
        return build(preorder, inorder, i, 0, inorder.size() - 1);
    }
};
