class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {

        long long ans = LLONG_MAX;

        vector<long long> choices = {
            0,
            min(need1, need2),
            max(need1, need2)
        };

        for (long long both : choices) {
            long long remaining1 = max(0LL, (long long)need1 - both);
            long long remaining2 = max(0LL, (long long)need2 - both);

            long long total = both * costBoth
                            + remaining1 * cost1
                            + remaining2 * cost2;

            ans = min(ans, total);
        }

        return ans;
    }
};
