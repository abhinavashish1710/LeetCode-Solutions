class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        unordered_map<Node*, Node*> mp;
        queue<Node*> q;

        mp[node] = new Node(node->val);
        q.push(node);

        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();

            for (Node* nei : cur->neighbors) {
                if (!mp.count(nei)) {
                    mp[nei] = new Node(nei->val);
                    q.push(nei);
                }
                mp[cur]->neighbors.push_back(mp[nei]);
            }
        }

        return mp[node];
    }
};
