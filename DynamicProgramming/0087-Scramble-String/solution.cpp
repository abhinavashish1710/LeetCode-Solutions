class Solution {
    map<pair<string,string>, bool> dp;

    bool solve(string a, string b) {
        if (a == b) return true;

        if (dp.count({a, b}))
            return dp[{a, b}];

        int n = a.size();

        // Pruning: both strings must have the same character frequencies
        string x = a, y = b;
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());

        if (x != y)
            return dp[{a, b}] = false;

        for (int i = 1; i < n; i++) {
            // No swap
            if (solve(a.substr(0, i), b.substr(0, i)) &&
                solve(a.substr(i), b.substr(i)))
                return dp[{a, b}] = true;

            // Swap
            if (solve(a.substr(0, i), b.substr(n - i)) &&
                solve(a.substr(i), b.substr(0, n - i)))
                return dp[{a, b}] = true;
        }

        return dp[{a, b}] = false;
    }

public:
    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size())
            return false;

        return solve(s1, s2);
    }
};
