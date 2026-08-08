class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;
        string cur;

        for (int i = 0; i <= path.size(); i++) {
            if (i == path.size() || path[i] == '/') {
                if (cur == "..") {
                    if (!st.empty()) st.pop_back();
                }
                else if (!cur.empty() && cur != ".") {
                    st.push_back(cur);
                }
                cur = "";
            }
            else {
                cur += path[i];
            }
        }

        string ans = "";
        for (string s : st)
            ans += "/" + s;

        return ans.empty() ? "/" : ans;
    }
};
