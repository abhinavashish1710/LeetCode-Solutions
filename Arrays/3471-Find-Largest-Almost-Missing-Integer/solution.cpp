class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int ans = -1;

        for (int x = 0; x <= 50; x++) {
            int cnt = 0;

            for (int i = 0; i + k <= nums.size(); i++) {
                for (int j = i; j < i + k; j++) {
                    if (nums[j] == x) {
                        cnt++;
                        break;
                    }
                }
            }

            if (cnt == 1)
                ans = x;
        }

        return ans;
    }
};
