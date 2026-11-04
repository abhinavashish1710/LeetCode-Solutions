class Solution {
private:
    static constexpr long long INF = 1e18;

    vector<long long> getMinOps(const vector<int>& nums, int x) {
        vector<long long> minOps(nums.size(), INF);
        multiset<int> lower;
        multiset<int> upper;
        long long lowerSum = 0;
        long long upperSum = 0;

        for (int i = 0; i < nums.size(); ++i) {
            if (lower.empty() || nums[i] <= *lower.rbegin()) {
                lower.insert(nums[i]);
                lowerSum += nums[i];
            } else {
                upper.insert(nums[i]);
                upperSum += nums[i];
            }

            if (i >= x) {
                int outNum = nums[i - x];
                auto it = lower.find(outNum);
                if (it != lower.end()) {
                    lower.erase(it);
                    lowerSum -= outNum;
                } else {
                    upper.erase(upper.find(outNum));
                    upperSum -= outNum;
                }
            }

            if (lower.size() < upper.size()) {
                int val = *upper.begin();
                upper.erase(upper.begin());
                lower.insert(val);
                upperSum -= val;
                lowerSum += val;
            } else if (lower.size() - upper.size() > 1) {
                int val = *lower.rbegin();
                lower.erase(prev(lower.end()));
                upper.insert(val);
                lowerSum -= val;
                upperSum += val;
            }

            if (i >= x - 1) {
                long long median = *lower.rbegin();
                long long ops = (median * lower.size() - lowerSum) + (upperSum - median * upper.size());
                minOps[i] = ops; 
            }
        }
        return minOps;
    }

    long long solve(int i, int k, const vector<long long>& minOps, int x, vector<vector<long long>>& memo) {
        if (k == 0) return 0;
        if (i >= minOps.size()) return INF;
        if (memo[i][k] != -1) return memo[i][k];

        long long skip = solve(i + 1, k, minOps, x, memo);
        long long pick = INF;
        
        int endIndex = i + x - 1;
        if (endIndex < minOps.size() && minOps[endIndex] != INF) {
            pick = minOps[endIndex] + solve(endIndex + 1, k - 1, minOps, x, memo);
        }

        return memo[i][k] = min(skip, pick);
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        vector<long long> minOps = getMinOps(nums, x);
        int n = nums.size();
        vector<vector<long long>> memo(n + 1, vector<long long>(k + 1, -1));
        return solve(0, k, minOps, x, memo);
    }
};
