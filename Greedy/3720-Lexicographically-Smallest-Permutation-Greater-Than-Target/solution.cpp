class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Try changing the permutation from right to left.
        for (int pos = n - 1; pos >= 0; pos--) {

            vector<int> freq(26, 0);

            // Count all characters from s.
            for (char c : s) {
                freq[c - 'a']++;
            }

            string ans;

            // Keep the prefix equal to target.
            bool possible = true;

            for (int i = 0; i < pos; i++) {
                int c = target[i] - 'a';

                if (freq[c] == 0) {
                    possible = false;
                    break;
                }

                freq[c]--;
                ans += target[i];
            }

            if (!possible) {
                continue;
            }

            // At pos, choose the smallest character
            // greater than target[pos].
            int targetChar = target[pos] - 'a';

            int greaterChar = -1;

            for (int c = targetChar + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    greaterChar = c;
                    break;
                }
            }

            if (greaterChar == -1) {
                continue;
            }

            ans += char('a' + greaterChar);
            freq[greaterChar]--;

            // Fill remaining positions with the smallest
            // possible characters.
            for (int c = 0; c < 26; c++) {
                ans += string(freq[c], char('a' + c));
            }

            return ans;
        }

        return "";
    }
};
