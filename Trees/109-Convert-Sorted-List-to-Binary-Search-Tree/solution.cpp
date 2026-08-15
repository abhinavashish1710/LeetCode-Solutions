class Solution {
public:
    TreeNode* build(vector<int>& v, int l, int r) {
        if (l > r) return nullptr;

        int m = (l + r) / 2;
        TreeNode* root = new TreeNode(v[m]);

        root->left = build(v, l, m - 1);
        root->right = build(v, m + 1, r);

        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        vector<int> v;

        while (head) {
            v.push_back(head->val);
            head = head->next;
        }

        return build(v, 0, v.size() - 1);
    }
};
