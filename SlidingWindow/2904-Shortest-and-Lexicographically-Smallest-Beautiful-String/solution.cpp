class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int left = 0;
        int ones = 0;
        string ans = "";

        for (int right = 0; right < s.size(); right++) {
            if (s[right] == '1') {
                ones++;
            }

            // More than k ones, shrink the window
            while (ones > k) {
                if (s[left] == '1') {
                    ones--;
                }
                left++;
            }

            // Exactly k ones
            if (ones == k) {
                // Remove unnecessary leading zeroes
                while (s[left] == '0') {
                    left++;
                }

                string current = s.substr(left, right - left + 1);

                // Shorter is better
                if (ans == "" || current.size() < ans.size()) {
                    ans = current;
                }
                // Same length -> lexicographically smaller
                else if (current.size() == ans.size() && current < ans) {
                    ans = current;
                }
            }
        }

        return ans;
    }
};
