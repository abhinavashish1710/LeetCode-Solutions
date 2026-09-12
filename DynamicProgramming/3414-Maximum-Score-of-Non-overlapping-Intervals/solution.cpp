#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class Solution {
    struct Interval {
        long long l, r, weight;
        int original_idx;
        
        bool operator<(const Interval& other) const {
            if (l != other.l) return l < other.l;
            if (r != other.r) return r < other.r;
            if (weight != other.weight) return weight > other.weight;
            return original_idx < other.original_idx;
        }
    };

    struct DPState {
        long long weight = 0;
        vector<int> indices;

        bool isBetterThan(const DPState& other) const {
            if (weight != other.weight) {
                return weight > other.weight;
            }
            return indices < other.indices;
        }
    };

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Interval> sorted_intervals(n);
        
        for (int i = 0; i < n; ++i) {
            sorted_intervals[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }
        
        sort(sorted_intervals.begin(), sorted_intervals.end());
        
        vector<long long> start_times(n);
        for (int i = 0; i < n; ++i) {
            start_times[i] = sorted_intervals[i].l;
        }

        // dp[i][k] stores the best outcome using at most k intervals from suffix [i...n-1]
        vector<vector<DPState>> dp(n + 1, vector<DPState>(5));

        for (int i = n - 1; i >= 0; --i) {
            // Find the first interval starting strictly after the current interval's end time
            int next_idx = upper_bound(start_times.begin() + i + 1, start_times.end(), sorted_intervals[i].r) - start_times.begin();

            for (int k = 1; k <= 4; ++k) {
                // Option 1: Skip interval i
                DPState best = dp[i + 1][k];

                // Option 2: Take interval i
                DPState take;
                take.weight = sorted_intervals[i].weight + dp[next_idx][k - 1].weight;
                take.indices = dp[next_idx][k - 1].indices;
                take.indices.push_back(sorted_intervals[i].original_idx);
                sort(take.indices.begin(), take.indices.end());

                if (take.isBetterThan(best)) {
                    best = take;
                }

                dp[i][k] = best;
            }
        }

        return dp[0][4].indices;
    }
};
