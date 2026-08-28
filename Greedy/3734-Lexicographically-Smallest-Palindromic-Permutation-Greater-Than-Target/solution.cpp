class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        int odd = 0;
        int middle = -1;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                middle = i;
            }
        }

        if (odd > 1) {
            return "";
        }

        vector<int> halfFreq(26);

        for (int i = 0; i < 26; i++) {
            halfFreq[i] = freq[i] / 2;
        }

        int halfLen = n / 2;
        string targetHalf = target.substr(0, halfLen);

        auto buildPalindrome = [&](string half, int mid) {
            string ans = half;

            if (mid != -1) {
                ans += char('a' + mid);
            }

            reverse(half.begin(), half.end());
            ans += half;

            return ans;
        };

        for (int pos = halfLen - 1; pos >= 0; pos--) {

            vector<int> cnt = halfFreq;
            bool possible = true;

            for (int i = 0; i < pos; i++) {
                int c = targetHalf[i] - 'a';

                if (cnt[c] == 0) {
                    possible = false;
                    break;
                }

                cnt[c]--;
            }

            if (!possible) {
                continue;
            }

            int targetChar = targetHalf[pos] - 'a';

            for (int c = targetChar + 1; c < 26; c++) {

                if (cnt[c] == 0) {
                    continue;
                }

                cnt[c]--;

                string half;

                for (int i = 0; i < pos; i++) {
                    half += targetHalf[i];
                }

                half += char('a' + c);

                for (int x = 0; x < 26; x++) {
                    half += string(cnt[x], char('a' + x));
                }

                string ans = buildPalindrome(half, middle);

                if (ans > target) {
                    return ans;
                }

                cnt[c]++;
            }
        }

        // First half exactly matches target's first half.
        vector<int> cnt = halfFreq;
        string half;

        for (char c : targetHalf) {
            int x = c - 'a';

            if (cnt[x] == 0) {
                return "";
            }

            cnt[x]--;
            half += c;
        }

        // For odd length, try a greater middle character.
        if (n % 2 == 1) {
            int targetMiddle = target[halfLen] - 'a';

            if (middle > targetMiddle) {
                return buildPalindrome(half, middle);
            }
        }

        return "";
    }
};
