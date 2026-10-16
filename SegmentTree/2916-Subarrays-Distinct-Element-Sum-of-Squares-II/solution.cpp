class Solution {
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0, sq = 0, lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int node, int l, int r, long long val) {
        long long len = r - l + 1;
        tree[node].sq = (tree[node].sq
            + 2 * val % MOD * tree[node].sum
            + len % MOD * val % MOD * val) % MOD;
        tree[node].sum = (tree[node].sum + len * val) % MOD;
        tree[node].lazy = (tree[node].lazy + val) % MOD;
    }

    void push(int node, int l, int r) {
        if (!tree[node].lazy || l == r) return;

        int mid = (l + r) / 2;
        apply(node * 2, l, mid, tree[node].lazy);
        apply(node * 2 + 1, mid + 1, r, tree[node].lazy);
        tree[node].lazy = 0;
    }

    void update(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            apply(node, l, r, 1);
            return;
        }

        push(node, l, r);
        int mid = (l + r) / 2;

        if (ql <= mid)
            update(node * 2, l, mid, ql, qr);
        if (qr > mid)
            update(node * 2 + 1, mid + 1, r, ql, qr);

        tree[node].sum = (tree[node * 2].sum
                        + tree[node * 2 + 1].sum) % MOD;
        tree[node].sq = (tree[node * 2].sq
                       + tree[node * 2 + 1].sq) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        vector<int> last(100001, -1);

        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int start = last[nums[i]] + 1;
            update(1, 0, n - 1, start, i);
            last[nums[i]] = i;
            ans = (ans + tree[1].sq) % MOD;
        }

        return ans;
    }
};
