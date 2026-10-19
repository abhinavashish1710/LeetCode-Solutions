class SummaryRanges {
    map<int, int> intervals;

public:
    SummaryRanges() {}

    void addNum(int value) {
        auto it = intervals.upper_bound(value);

        if (it != intervals.begin()) {
            auto prev = std::prev(it);
            if (prev->second >= value) return;

            if (prev->second + 1 == value) {
                prev->second = value;

                if (it != intervals.end() && it->first == value + 1) {
                    prev->second = it->second;
                    intervals.erase(it);
                }
                return;
            }
        }

        if (it != intervals.end() && it->first == value + 1) {
            int end = it->second;
            intervals.erase(it);
            intervals[value] = end;
        } else {
            intervals[value] = value;
        }
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> ans;

        for (auto [start, end] : intervals)
            ans.push_back({start, end});

        return ans;
    }
};

