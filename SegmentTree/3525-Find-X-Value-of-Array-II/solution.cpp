#include <vector>

using namespace std;

struct Node {
    int remain[5] = {0};
    int prod = 1;
};

class SegmentTree {
private:
    int n;
    int k;
    vector<Node> tree;

    // Combines information from two sub-segments
    Node merge(const Node& left, const Node& right) const {
        Node res;
        res.prod = (left.prod * right.prod) % k;
        
        // 1. Prefixes contained entirely in the left segment
        for (int r = 0; r < k; ++r) {
            res.remain[r] = left.remain[r];
        }
        
        // 2. Prefixes extending into the right segment
        for (int r = 0; r < k; ++r) {
            res.remain[(r * left.prod) % k] += right.remain[r];
        }
        
        return res;
    }

    void build(const vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            int val = nums[start] % k;
            tree[node].prod = val;
            tree[node].remain[val] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        build(nums, 2 * node, start, mid);
        build(nums, 2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            for (int r = 0; r < k; ++r) {
                tree[node].remain[r] = 0;
            }
            int rem = val % k;
            tree[node].prod = rem;
            tree[node].remain[rem] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int start, int end, int l, int r) const {
        if (r < start || end < l) {
            return Node();
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        if (r <= mid) return query(2 * node, start, mid, l, r);
        if (l > mid) return query(2 * node + 1, mid + 1, end, l, r);
        
        return merge(
            query(2 * node, start, mid, l, r),
            query(2 * node + 1, mid + 1, end, l, r)
        );
    }

public:
    SegmentTree(const vector<int>& nums, int k) : n(nums.size()), k(k), tree(4 * nums.size()) {
        build(nums, 1, 0, n - 1);
    }

    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    Node query(int l, int r) const {
        return query(1, 0, n - 1, l, r);
    }
};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        SegmentTree st(nums, k);
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int idx = q[0];
            int val = q[1];
            int start = q[2];
            int x = q[3];

            // 1. Persistently update nums[idx] = val
            st.update(idx, val);

            // 2. Query prefix product count modulo k in subarray nums[start..n-1]
            Node res = st.query(start, nums.size() - 1);
            ans.push_back(res.remain[x]);
        }

        return ans;
    }
};
