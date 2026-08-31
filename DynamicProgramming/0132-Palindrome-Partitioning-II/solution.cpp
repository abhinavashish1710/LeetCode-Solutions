class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<vector<bool>> p(n, vector<bool>(n));
        vector<int> dp(n + 1, INT_MAX);

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                p[i][j] = s[i] == s[j] &&
                          (j - i < 2 || p[i + 1][j - 1]);

        dp[0] = -1;

        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                if (p[j][i - 1])
                    dp[i] = min(dp[i], dp[j] + 1);

        return dp[n];
    }
};
