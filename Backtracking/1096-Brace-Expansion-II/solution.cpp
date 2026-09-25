class Solution {
public:
    string s;
    int pos = 0;

    set<string> parseExpression() {
        set<string> res = parseTerm();

        while (pos < s.size() && s[pos] == ',') {
            pos++;
            set<string> next = parseTerm();
            res.insert(next.begin(), next.end());
        }

        return res;
    }

    set<string> parseTerm() {
        set<string> res = {""};

        while (pos < s.size() && s[pos] != '}' && s[pos] != ',') {
            set<string> cur;

            if (s[pos] == '{') {
                pos++;
                cur = parseExpression();
                pos++; // skip '}'
            } else {
                cur.insert(string(1, s[pos]));
                pos++;
            }

            set<string> next;

            for (string a : res)
                for (string b : cur)
                    next.insert(a + b);

            res = next;
        }

        return res;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;

        set<string> res = parseExpression();

        return vector<string>(res.begin(), res.end());
    }
};
