class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> reward(n, 1);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j &&
                    items[j][0] % items[i][0] == 0) {
                    reward[i]++;
                }
            }
        }

        const int NEG = -1000000000;

        vector<int> dp(budget + 1, NEG);
        dp[0] = 0;

        int ans = 0;

        for (int p = 1500; p >= 1; p--) {

    
            vector<int> used(budget + 1, NEG);

            for (int i = 0; i < n; i++) {
                if (items[i][1] != p) continue;

                int cost = items[i][1];
                int value = reward[i];

                for (int c = budget; c >= cost; c--) {
                    if (dp[c - cost] != NEG) {
                        used[c] = max(
                            used[c],
                            dp[c - cost] + value
                        );
                    }

                    if (used[c - cost] != NEG) {
                        used[c] = max(
                            used[c],
                            used[c - cost] + value
                        );
                    }
                }
            }

            for (int c = 0; c <= budget; c++) {
                if (used[c] == NEG) continue;

                int extra = (budget - c) / p;
                ans = max(ans, used[c] + extra);
            }

            for (int i = 0; i < n; i++) {
                if (items[i][1] != p) continue;

                int cost = p;
                int value = reward[i];

                for (int c = budget; c >= cost; c--) {
                    if (dp[c - cost] != NEG) {
                        dp[c] = max(
                            dp[c],
                            dp[c - cost] + value
                        );
                    }
                }
            }
        }

        return ans;
    }
};
