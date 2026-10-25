class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> events;
        
        for (const auto& b : buildings) {
            events.push_back({b[0], -b[2]});
            events.push_back({b[1], b[2]});
        }
        
        sort(events.begin(), events.end());
        
        vector<vector<int>> result;
        multiset<int> activeHeights = {0};
        int prevMaxHeight = 0;
        
        for (const auto& event : events) {
            int x = event.first;
            int h = event.second;
            
            if (h < 0) {
                activeHeights.insert(-h);
            } else {
                activeHeights.erase(activeHeights.find(h));
            }
            
            int currentMaxHeight = *activeHeights.rbegin();
            
            if (currentMaxHeight != prevMaxHeight) {
                result.push_back({x, currentMaxHeight});
                prevMaxHeight = currentMaxHeight;
            }
        }
        
        return result;
    }
};
