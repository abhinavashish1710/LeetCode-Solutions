class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        for (int multiple = k; ; multiple += k) {
            bool found = false;

            for (int x : nums) {
                if (x == multiple) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return multiple;
            }
        }
    }
};
