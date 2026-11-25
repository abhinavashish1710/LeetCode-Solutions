class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        const long long MOD1 = 1000000007LL;
        const long long MOD2 = 1000000009LL;
        const long long BASE1 = 100003LL;
        const long long BASE2 = 100019LL;

        vector<long long> pow1(n + 1, 1), pow2(n + 1, 1);
        vector<long long> pref1(n + 1, 0), pref2(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            long long val = nums[i];
            pow1[i + 1] = (pow1[i] * BASE1) % MOD1;
            pow2[i + 1] = (pow2[i] * BASE2) % MOD2;
            pref1[i + 1] = (pref1[i] * BASE1 + val) % MOD1;
            pref2[i + 1] = (pref2[i] * BASE2 + val) % MOD2;
        }

        auto hasUniqueOfLen = [&](int len) -> bool {
            unordered_map<unsigned long long, int> freq;
            freq.reserve(n - len + 1);
            for (int i = 0; i + len <= n; ++i) {
                int j = i + len;
                long long h1 = (pref1[j] - (pref1[i] * pow1[len]) % MOD1 + MOD1) % MOD1;
                long long h2 = (pref2[j] - (pref2[i] * pow2[len]) % MOD2 + MOD2) % MOD2;
                unsigned long long key = (static_cast<unsigned long long>(h1) << 32) | static_cast<unsigned long long>(h2);
                ++freq[key];
            }
            for (const auto& kv : freq) {
                if (kv.second == 1) {
                    return true;
                }
            }
            return false;
        };

        int low = 1, high = n, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hasUniqueOfLen(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};
