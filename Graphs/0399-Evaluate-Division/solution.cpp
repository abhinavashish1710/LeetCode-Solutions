class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations,
                                vector<double>& values,
                                vector<vector<string>>& queries) {
        unordered_map<string, vector<pair<string, double>>> graph;

        for (int i = 0; i < equations.size(); i++) {
            string a = equations[i][0], b = equations[i][1];
            graph[a].push_back({b, values[i]});
            graph[b].push_back({a, 1.0 / values[i]});
        }

        vector<double> ans;

        for (auto& q : queries) {
            string src = q[0], dst = q[1];

            if (!graph.count(src) || !graph.count(dst)) {
                ans.push_back(-1.0);
                continue;
            }

            unordered_set<string> visited;
            queue<pair<string, double>> qu;
            qu.push({src, 1.0});
            visited.insert(src);

            double result = -1.0;

            while (!qu.empty()) {
                auto [cur, val] = qu.front();
                qu.pop();

                if (cur == dst) {
                    result = val;
                    break;
                }

                for (auto& [next, weight] : graph[cur]) {
                    if (!visited.count(next)) {
                        visited.insert(next);
                        qu.push({next, val * weight});
                    }
                }
            }

            ans.push_back(result);
        }

        return ans;
    }
};
