class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int maxi = nums.back();

        vector<int> dp(maxi + 2, 0);

        int ans = 0;

        for (int x : nums) {
            int keep = dp[x - 1] + 1;
            int increase = dp[x] + 1;

            dp[x] = max(dp[x], keep);
            dp[x + 1] = max(dp[x + 1], increase);

            ans = max(ans, max(dp[x], dp[x + 1]));
        }

        return ans;
    }
};
