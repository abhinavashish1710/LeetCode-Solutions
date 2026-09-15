class BSTIterator {
public:
    stack<TreeNode*> st;

    BSTIterator(TreeNode* root) {
        pushLeft(root);
    }

    void pushLeft(TreeNode* root) {
        while(root) {
            st.push(root);
            root = root->left;
        }
    }

    int next() {
        TreeNode* node = st.top();
        st.pop();

        pushLeft(node->right);

        return node->val;
    }

    bool hasNext() {
        return !st.empty();
    }
};
