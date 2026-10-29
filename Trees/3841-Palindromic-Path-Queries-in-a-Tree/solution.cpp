#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
    int n;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos;
    vector<int> tree;
    int cur_pos;

    int dfs(int v, int p, int d) {
        parent[v] = p;
        depth[v] = d;
        int size = 1;
        int max_c_size = 0;
        for (int u : adj[v]) {
            if (u != p) {
                int c_size = dfs(u, v, d + 1);
                size += c_size;
                if (c_size > max_c_size) {
                    max_c_size = c_size;
                    heavy[v] = u;
                }
            }
        }
        return size;
    }

    void decompose(int v, int h) {
        head[v] = h;
        pos[v] = cur_pos++;
        if (heavy[v] != -1) {
            decompose(heavy[v], h);
        }
        for (int u : adj[v]) {
            if (u != parent[v] && u != heavy[v]) {
                decompose(u, u);
            }
        }
    }

    void build_seg(int node, int l, int r, const vector<int>& initial_masks) {
        if (l == r) {
            tree[node] = initial_masks[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build_seg(2 * node, l, mid, initial_masks);
        build_seg(2 * node + 1, mid + 1, r, initial_masks);
        tree[node] = tree[2 * node] ^ tree[2 * node + 1];
    }

    void update_seg(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = l + (r - l) / 2;
        if (idx <= mid) update_seg(2 * node, l, mid, idx, val);
        else update_seg(2 * node + 1, mid + 1, r, idx, val);
        tree[node] = tree[2 * node] ^ tree[2 * node + 1];
    }

    int query_seg(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = l + (r - l) / 2;
        return query_seg(2 * node, l, mid, ql, qr) ^ query_seg(2 * node + 1, mid + 1, r, ql, qr);
    }

    int query_path(int u, int v) {
        int res = 0;
        for (; head[u] != head[v]; v = parent[head[v]]) {
            if (depth[head[u]] > depth[head[v]]) swap(u, v);
            res ^= query_seg(1, 0, n - 1, pos[head[v]], pos[v]);
        }
        if (depth[u] > depth[v]) swap(u, v);
        res ^= query_seg(1, 0, n - 1, pos[u], pos[v]);
        return res;
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        this->n = n;
        adj.assign(n, vector<int>());
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        parent.assign(n, 0);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        cur_pos = 0;

        dfs(0, 0, 0);
        decompose(0, 0);

        vector<int> initial_masks(n);
        for (int i = 0; i < n; ++i) {
            initial_masks[pos[i]] = (1 << (s[i] - 'a'));
        }

        tree.assign(4 * n, 0);
        build_seg(1, 0, n - 1, initial_masks);

        vector<bool> answer;
        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;
            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;
                int new_mask = (1 << (c - 'a'));
                update_seg(1, 0, n - 1, pos[u], new_mask);
            } else {
                int u, v;
                ss >> u >> v;
                int path_mask = query_path(u, v);
                bool is_palindrome = (path_mask == 0 || (path_mask & (path_mask - 1)) == 0);
                answer.push_back(is_palindrome);
            }
        }

        return answer;
    }
};
