class Solution {
public:
    int ans=0;

    pair<int,int> dfs(TreeNode* r){
        if(!r) return {0,0};

        auto l=dfs(r->left);
        auto q=dfs(r->right);

        int sum=l.first+q.first+r->val;
        int cnt=l.second+q.second+1;

        if(sum/cnt==r->val) ans++;
        return {sum,cnt};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
