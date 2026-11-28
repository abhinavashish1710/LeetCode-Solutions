#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> freq(n + 1, 0);
        for (const auto& item : items) {
            freq[item[0]]++;
        }

        vector<int> mult(n + 1, 0);
        for (int f = 1; f <= n; ++f) {
            if (freq[f] > 0) {
                for (int m = f; m <= n; m += f) {
                    mult[f] += freq[m];
                }
            }
        }

        long long min_p = 2e9;
        vector<pair<long long, long long>> double_items;
        double_items.reserve(n);

        for (const auto& item : items) {
            int f = item[0];
            long long p = item[1];
            min_p = min(min_p, p);
            long long k = mult[f] - 1;
            if (k > 0) {
                double_items.push_back({p, k});
            }
        }

        sort(double_items.begin(), double_items.end());

        long long rem = budget;
        long long cur_double_items = 0;
        long long ans = rem / min_p;

        for (const auto& [p, k] : double_items) {
            if (rem < p) break;
            long long take = min(k, rem / p);
            rem -= take * p;
            cur_double_items += 2 * take;
            ans = max(ans, cur_double_items + rem / min_p);
        }

        return ans;
    }
};
