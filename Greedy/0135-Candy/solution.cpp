#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int candy(std::vector<int>& ratings) {
        int n = ratings.size();
        if (n == 0) return 0;

        // Step 1: Initialize everyone with 1 candy
        std::vector<int> candies(n, 1);

        // Step 2: Left-to-Right Pass
        // Compare with left neighbor
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // Step 3: Right-to-Left Pass
        // Compare with right neighbor and take the maximum required
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = std::max(candies[i], candies[i + 1] + 1);
            }
        }

        // Step 4: Sum up total candies
        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};
