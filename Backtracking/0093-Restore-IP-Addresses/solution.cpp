class Solution {
public:
    vector<string> ans;
    vector<string> parts;

    void solve(string& s, int start) {
        if (parts.size() == 4) {
            if (start == s.size()) {
                string ip = parts[0] + "." + parts[1] + "." +
                            parts[2] + "." + parts[3];
                ans.push_back(ip);
            }
            return;
        }

        for (int len = 1; len <= 3 && start + len <= s.size(); len++) {
            string part = s.substr(start, len);

            if (part.size() > 1 && part[0] == '0')
                continue;

            if (stoi(part) > 255)
                continue;

            parts.push_back(part);
            solve(s, start + len);
            parts.pop_back();
        }
    }

    vector<string> restoreIpAddresses(string s) {
        if (s.size() < 4 || s.size() > 12)
            return {};

        solve(s, 0);
        return ans;
    }
};
