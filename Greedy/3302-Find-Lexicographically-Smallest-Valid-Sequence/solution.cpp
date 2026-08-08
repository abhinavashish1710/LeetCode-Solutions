class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();

        // positions of every character in word1
        vector<int> pos[26];
        for (int i = 0; i < n; i++)
            pos[word1[i] - 'a'].push_back(i);

        // r0[j] = latest possible index of word2[j]
        // such that word2[j..] is an exact subsequence.
        vector<int> r0(m + 1, -1), r1(m + 1, -1);

        r0[m] = r1[m] = n;

        for (int j = m - 1; j >= 0; j--) {
            // Exact match
            auto &v = pos[word2[j] - 'a'];
            auto it = lower_bound(v.begin(), v.end(), r0[j + 1]);

            if (it != v.begin()) {
                --it;
                r0[j] = *it;
            }

            // At most one mismatch
            // Case 1: current character matches, suffix may have 1 mismatch
            auto it1 = lower_bound(v.begin(), v.end(), r1[j + 1]);
            if (it1 != v.begin()) {
                --it1;
                r1[j] = *it1;
            }

            // Case 2: current character is the one mismatch
            // Find latest index < r0[j+1] whose char != word2[j]
            int x = r0[j + 1] - 1;

            if (x >= 0 && word1[x] == word2[j])
                x--;

            if (x >= 0)
                r1[j] = max(r1[j], x);
        }

        // If even the whole word cannot be formed with <= 1 mismatch
        if (r1[0] == -1)
            return {};

        vector<int> ans;
        int prev = -1;
        bool usedMismatch = false;

        for (int j = 0; j < m; j++) {
            int best = n;

            // Option 1: use exact character
            int limit = usedMismatch ? r0[j + 1] : r1[j + 1];

            auto &v = pos[word2[j] - 'a'];
            auto it = upper_bound(v.begin(), v.end(), prev);

            if (it != v.end() && *it < limit)
                best = min(best, *it);

            // Option 2: use this position as the one mismatch
            if (!usedMismatch) {
                int x = prev + 1;

                while (x < r0[j + 1] && word1[x] == word2[j])
                    x++;

                if (x < r0[j + 1])
                    best = min(best, x);
            }

            if (best == n)
                return {};

            if (word1[best] != word2[j])
                usedMismatch = true;

            ans.push_back(best);
            prev = best;
        }

        return ans;
    }
};
