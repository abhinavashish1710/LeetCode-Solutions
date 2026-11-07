class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> freeServers;
        for (int i = 0; i < n; ++i) {
            freeServers.push({servers[i], i});
        }
        
        priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> busyServers;
        
        vector<int> ans(m);
        long long current_time = 0;
        
        for (int j = 0; j < m; ++j) {
            current_time = max(current_time, (long long)j);
            
            while (!busyServers.empty() && busyServers.top().first <= current_time) {
                auto top = busyServers.top();
                busyServers.pop();
                long long free_time = top.first;
                int weight = top.second.first;
                int idx = top.second.second;
                freeServers.push({weight, idx});
            }
            
            if (freeServers.empty()) {
                current_time = busyServers.top().first;
                while (!busyServers.empty() && busyServers.top().first <= current_time) {
                    auto top = busyServers.top();
                    busyServers.pop();
                    long long free_time = top.first;
                    int weight = top.second.first;
                    int idx = top.second.second;
                    freeServers.push({weight, idx});
                }
            }
            
            auto server = freeServers.top();
            freeServers.pop();
            int weight = server.first;
            int idx = server.second;
            
            ans[j] = idx;
            busyServers.push({current_time + tasks[j], {weight, idx}});
        }
        
        return ans;
    }
};
