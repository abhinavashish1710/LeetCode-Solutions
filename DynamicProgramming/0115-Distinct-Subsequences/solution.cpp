#include <string>
#include <vector>

class Solution {
public:
    int numDistinct(std::string s, std::string t) {
        int m = s.length();
        int n = t.length();

        // Edge case: target is longer than source string
        if (m < n) return 0;


        std::vector<unsigned int> dp(n + 1, 0);

        
        dp[0] = 1;

        for (int i = 1; i <= m; ++i) {
            // Iterate backwards so we use the previous row's dp values
            for (int j = n; j >= 1; --j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return dp[n];
    }
};
