class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        vector<int> pre(n + 1);
        for (int i = 0; i < n; i++)
            pre[i + 1] = pre[i] + stoneValue[i];

        vector<vector<int>> dp(n, vector<int>(n));

        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len <= n; l++) {
                int r = l + len - 1;

                for (int k = l; k < r; k++) {
                    int left = pre[k + 1] - pre[l];
                    int right = pre[r + 1] - pre[k + 1];

                    if (left < right)
                        dp[l][r] = max(dp[l][r], left + dp[l][k]);
                    else if (right < left)
                        dp[l][r] = max(dp[l][r], right + dp[k + 1][r]);
                    else
                        dp[l][r] = max(dp[l][r],
                                       left + max(dp[l][k], dp[k + 1][r]));
                }
            }
        }

        return dp[0][n - 1];
    }
};
