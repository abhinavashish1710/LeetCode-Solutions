class Solution {
public:
    vector<vector<string>> ans;
    vector<string> path;

    bool isPal(string &s, int l, int r) {
        while (l < r)
            if (s[l++] != s[r--]) return false;
        return true;
    }

    void dfs(string &s, int i) {
        if (i == s.size()) {
            ans.push_back(path);
            return;
        }

        for (int j = i; j < s.size(); j++) {
            if (isPal(s, i, j)) {
                path.push_back(s.substr(i, j - i + 1));
                dfs(s, j + 1);
                path.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        dfs(s, 0);
        return ans;
    }
};
