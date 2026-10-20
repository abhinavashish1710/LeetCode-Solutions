class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        long long totalSum = 0;

        for (int k = 1; k <= n; ++k) {
            if (n % k != 0) continue;

            bool possible = true;
            int prevMax = -1;

            for (int i = 0; i < n; i += k) {
                int drops = 0;
                for (int j = 0; j < k; ++j) {
                    if (nums[i + j] > nums[i + (j + 1) % k]) {
                        drops++;
                    }
                }

                if (drops > 1) {
                    possible = false;
                    break;
                }

                int dropIdx = 0;
                for (int j = 0; j < k; ++j) {
                    if (nums[i + j] > nums[i + (j + 1) % k]) {
                        dropIdx = (j + 1) % k;
                        break;
                    }
                }

                vector<int> sortedBlock(k);
                for (int j = 0; j < k; ++j) {
                    sortedBlock[j] = nums[i + (dropIdx + j) % k];
                }

                if (i > 0 && prevMax > sortedBlock[0]) {
                    possible = false;
                    break;
                }

                prevMax = sortedBlock.back();
            }

            if (possible) {
                totalSum += k;
            }
        }

        return totalSum;
    }
};
