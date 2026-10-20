class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;

    void dfs(int start, int k, int sum) {
        if (path.size() == k) {
            if (sum == 0) ans.push_back(path);
            return;
        }

        for (int i = start; i <= 9; i++) {
            if (i > sum) break;

            path.push_back(i);
            dfs(i + 1, k, sum - i);
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        dfs(1, k, n);
        return ans;
    }
};
