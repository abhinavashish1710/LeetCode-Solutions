class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int len = m + n - 1;

        // A valid parentheses string must have even length.
        if (len % 2)
            return false;

        // The path must start with '('.
        if (grid[0][0] == ')')
            return false;

        // dp[i][j][balance] = whether this balance is possible at (i,j)
        vector<vector<vector<bool>>> dp(
            m, vector<vector<bool>>(n, vector<bool>(len + 1, false))
        );

        dp[0][0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0)
                    continue;

                int change = (grid[i][j] == '(' ? 1 : -1);

                for (int balance = 0; balance <= len; balance++) {
                    int prev = balance - change;

                    if (prev < 0 || prev > len)
                        continue;

                    bool possible = false;

                    if (i > 0)
                        possible |= dp[i - 1][j][prev];

                    if (j > 0)
                        possible |= dp[i][j - 1][prev];

                    dp[i][j][balance] = possible;
                }
            }
        }

        return dp[m - 1][n - 1][0];
    }
};
