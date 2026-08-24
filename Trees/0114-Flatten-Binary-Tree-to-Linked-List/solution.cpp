class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr)
            return;

        flatten(root->left);
        flatten(root->right);

        TreeNode* temp = root->right;

        root->right = root->left;
        root->left = nullptr;

        TreeNode* curr = root;
        while (curr->right != nullptr)
            curr = curr->right;

        curr->right = temp;
    }
};
