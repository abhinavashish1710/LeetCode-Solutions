#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    struct Target {
        int a = 0, b = 0, c = 0, d = 0;
    };

    bool factorize(long long t, Target& target) {
        while (t % 2 == 0) { target.a++; t /= 2; }
        while (t % 3 == 0) { target.b++; t /= 3; }
        while (t % 5 == 0) { target.c++; t /= 5; }
        while (t % 7 == 0) { target.d++; t /= 7; }
        return t == 1;
    }

    Target consume(Target req, int digit) {
        if (digit <= 1) return req;
        int d = digit;
        while (d % 2 == 0) { req.a = max(0, req.a - 1); d /= 2; }
        while (d % 3 == 0) { req.b = max(0, req.b - 1); d /= 3; }
        while (d % 5 == 0) { req.c = max(0, req.c - 1); d /= 5; }
        while (d % 7 == 0) { req.d = max(0, req.d - 1); d /= 7; }
        return req;
    }

    int minDigitsNeeded(const Target& req) {
        int a = req.a, b = req.b, c = req.c, d = req.d;
        int count = c + d;

        int n9 = b / 2; b %= 2;
        int n8 = a / 3; a %= 3;

        int n6 = 0;
        if (a == 1 && b == 1) { n6 = 1; a = 0; b = 0; }
        else if (a == 2 && b == 1) { n6 = 1; a = 1; b = 0; }

        int n4 = a / 2; a %= 2;
        int n3 = b;
        int n2 = a;

        return count + n9 + n8 + n6 + n4 + n3 + n2;
    }

    string buildSuffix(Target req, int len) {
        int a = req.a, b = req.b, c = req.c, d = req.d;

        int n5 = c, n7 = d;
        int n9 = b / 2; b %= 2;
        int n8 = a / 3; a %= 3;

        int n6 = 0;
        if (a == 1 && b == 1) { n6 = 1; a = 0; b = 0; }
        else if (a == 2 && b == 1) { n6 = 1; a = 1; b = 0; }

        int n4 = a / 2; a %= 2;
        int n3 = b;
        int n2 = a;

        int used = n2 + n3 + n4 + n5 + n6 + n7 + n8 + n9;
        int n1 = len - used;

        string suffix = "";
        suffix.reserve(len);
        suffix.append(n1, '1');
        suffix.append(n2, '2');
        suffix.append(n3, '3');
        suffix.append(n4, '4');
        suffix.append(n5, '5');
        suffix.append(n6, '6');
        suffix.append(n7, '7');
        suffix.append(n8, '8');
        suffix.append(n9, '9');

        return suffix;
    }

public:
    string smallestNumber(string num, long long t) {
        Target req;
        if (!factorize(t, req)) return "-1";

        int n = num.size();

        // Check if `num` contains zero
        int zeroIdx = num.find('0');
        int maxI = (zeroIdx == string::npos) ? n - 1 : zeroIdx;

        // Precompute prefix requirement: prefReq[i] stores requirements remaining for num[0...i-1]
        vector<Target> prefReq(n + 1);
        prefReq[0] = req;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') break;
            prefReq[i + 1] = consume(prefReq[i], num[i] - '0');
        }

        // Step 1: Check if 'num' itself is valid (only if zero-free)
        if (zeroIdx == string::npos && minDigitsNeeded(prefReq[n]) == 0) {
            return num;
        }

        // Step 2: Try to match prefix of length i and increase digit at index i
        for (int i = maxI; i >= 0; --i) {
            Target currentReq = prefReq[i];
            int startDigit = (num[i] - '0') + 1;

            for (int d = startDigit; d <= 9; ++d) {
                Target nextReq = consume(currentReq, d);
                int remLen = n - 1 - i;

                if (minDigitsNeeded(nextReq) <= remLen) {
                    string ans = num.substr(0, i);
                    ans += to_string(d);
                    ans += buildSuffix(nextReq, remLen);
                    return ans;
                }
            }
        }

        // Step 3: If no valid length n number exists, find smallest length n + 1
        int totalLen = n + 1;
        while (true) {
            if (minDigitsNeeded(req) <= totalLen) {
                return buildSuffix(req, totalLen);
            }
            totalLen++;
        }
    }
};
