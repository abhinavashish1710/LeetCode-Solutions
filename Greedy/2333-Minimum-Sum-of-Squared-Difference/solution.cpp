class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        long long k = (long long)k1 + k2;
        vector<int> diff(nums1.size());

        long long total = 0;
        for (int i = 0; i < nums1.size(); i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total += diff[i];
        }

        if (total <= k)
            return 0;

        sort(diff.begin(), diff.end(), greater<int>());

        int n = diff.size();
        int low = 0, high = diff[0];

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long need = 0;

            for (int d : diff) {
                if (d > mid)
                    need += d - mid;
            }

            if (need <= k)
                high = mid;
            else
                low = mid + 1;
        }

        long long ans = 0;
        long long remaining = k;

        for (int d : diff) {
            if (d > low) {
                remaining -= d - low;
                ans += 1LL * low * low;
            } else {
                ans += 1LL * d * d;
            }
        }


        for (int d : diff) {
            if (remaining == 0)
                break;

            if (d >= low && d > 0) {
                ans -= 1LL * low * low;
                ans += 1LL * (low - 1) * (low - 1);
                remaining--;
            }
        }

        return ans;
    }
};
