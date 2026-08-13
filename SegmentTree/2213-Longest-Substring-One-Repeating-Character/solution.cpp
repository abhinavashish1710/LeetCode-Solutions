class Solution {
    struct Node {
        int len, pre, suf, best;
        char lc, rc;
    };

    vector<Node> st;

    Node merge(Node a, Node b) {
        if (!a.len) return b;
        if (!b.len) return a;

        Node c;
        c.len = a.len + b.len;
        c.lc = a.lc;
        c.rc = b.rc;
        c.pre = a.pre;
        c.suf = b.suf;
        c.best = max(a.best, b.best);

        if (a.rc == b.lc) {
            c.best = max(c.best, a.suf + b.pre);

            if (a.pre == a.len)
                c.pre += b.pre;

            if (b.suf == b.len)
                c.suf += a.suf;
        }

        return c;
    }

    void build(string &s, int p, int l, int r) {
        if (l == r) {
            st[p] = {1, 1, 1, 1, s[l], s[l]};
            return;
        }

        int m = (l + r) / 2;
        build(s, p * 2, l, m);
        build(s, p * 2 + 1, m + 1, r);
        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

    void update(int p, int l, int r, int idx, char ch) {
        if (l == r) {
            st[p] = {1, 1, 1, 1, ch, ch};
            return;
        }

        int m = (l + r) / 2;

        if (idx <= m)
            update(p * 2, l, m, idx, ch);
        else
            update(p * 2 + 1, m + 1, r, idx, ch);

        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        int n = s.size();
        st.resize(4 * n);

        build(s, 1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            int idx = queryIndices[i];
            char ch = queryCharacters[i];

            s[idx] = ch;
            update(1, 0, n - 1, idx, ch);

            ans.push_back(st[1].best);
        }

        return ans;
    }
};
