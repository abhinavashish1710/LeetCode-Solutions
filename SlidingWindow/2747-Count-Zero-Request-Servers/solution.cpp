class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = queries.size();
        vector<pair<int, int>> sorted_queries(m);
        for (int i = 0; i < m; ++i) {
            sorted_queries[i] = {queries[i], i};
        }
        
        sort(sorted_queries.begin(), sorted_queries.end());
        
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        vector<int> ans(m);
        unordered_map<int, int> server_counts;
        
        int l = 0, r = 0;
        int num_logs = logs.size();
        
        for (auto& q : sorted_queries) {
            int q_time = q.first;
            int idx = q.second;
            int start = q_time - x;
            int end = q_time;
            
            while (r < num_logs && logs[r][1] <= end) {
                server_counts[logs[r][0]]++;
                r++;
            }
            
            while (l < num_logs && logs[l][1] < start) {
                server_counts[logs[l][0]]--;
                if (server_counts[logs[l][0]] == 0) {
                    server_counts.erase(logs[l][0]);
                }
                l++;
            }
            
            ans[idx] = n - server_counts.size();
        }
        
        return ans;
    }
};
