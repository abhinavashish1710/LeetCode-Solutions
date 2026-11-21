class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent(n, -1);
        vector<int> last(26, -1);

        struct Event {
            int node;
            int prev;
            bool exit;
        };

        stack<Event> st;
        st.push({0, -1, false});

        while (!st.empty()) {
            Event e = st.top();
            st.pop();

            int u = e.node;
            int c = s[u] - 'a';

            if (e.exit) {
                last[c] = e.prev;
                continue;
            }

            int prev = last[c];

            if (u == 0) {
                newParent[u] = -1;
            }
            else if (prev != -1) {
                newParent[u] = prev;
            }
            else {
                newParent[u] = parent[u];
            }

            last[c] = u;

            st.push({u, prev, true});

            for (int v : adj[u]) {
                st.push({v, -1, false});
            }
        }

        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        vector<int> order;
        stack<int> dfs;
        dfs.push(0);

        while (!dfs.empty()) {
            int u = dfs.top();
            dfs.pop();

            order.push_back(u);

            for (int v : tree[u]) {
                dfs.push(v);
            }
        }

        vector<int> ans(n, 1);

        for (int i = order.size() - 1; i >= 0; i--) {
            int u = order[i];

            if (newParent[u] != -1) {
                ans[newParent[u]] += ans[u];
            }
        }

        return ans;
    }
};
