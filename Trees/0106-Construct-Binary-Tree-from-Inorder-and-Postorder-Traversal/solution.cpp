class Solution {
public:
    TreeNode* build(vector<int>& inorder, vector<int>& postorder, int& i, int l, int r) {
        if (l > r) return nullptr;

        TreeNode* root = new TreeNode(postorder[i--]);

        int mid = find(inorder.begin() + l, inorder.begin() + r + 1, root->val) - inorder.begin();

        root->right = build(inorder, postorder, i, mid + 1, r);
        root->left = build(inorder, postorder, i, l, mid - 1);

        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int i = postorder.size() - 1;
        return build(inorder, postorder, i, 0, inorder.size() - 1);
    }
};
