class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(!root) return ans;

        stack<TreeNode*> st;
        st.push(root);

        while(!st.empty()){
            TreeNode* cur=st.top();
            st.pop();
            ans.push_back(cur->val);

            if(cur->right) st.push(cur->right);
            if(cur->left) st.push(cur->left);
        }
        return ans;
    }
};
